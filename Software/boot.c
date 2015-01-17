// syscall_code
#define PRINT_INT 1
#define PRINT_STRING 4
#define READ_INT 5
#define READ_STRING 8
#define PRINT_CHAR 11
#define READ_CHAR 12
#define OPEN 13
#define READ 14
#define WRITE 15
#define CLOSE 16

// mipscom
#define OFFSET 0xffffd0f0   //存数据时的偏移量
#define COMADR 0xfe000000     //串口地址
// address
//#define READ_ADDR 0xffffd000
// #define POINTER	0xffffd0f0
//#define BUFFER	0xffffd0f4
#define FILE_BUFFER 0x00007a08
#define FILE_INFO 0x00007a00
#define VRAM 0x000c0000
#define KB_BUFFER 0x00007f00
#define CODE_SEGMENT 12
#define GPIO 0xffffff00
// global variable
#define CONSOLE (CODE_SEGMENT+16)
#define ERROR (CONSOLE+40)
#define CMD_DIR (ERROR+28)
#define CMD_TYPE (CMD_DIR+16)
#define CMD_RENAME (CMD_TYPE+20)
#define CMD_EXIT (CMD_RENAME+16)
#define CMD_DEL (CMD_EXIT+20)
#define CMD_TOUCH (CMD_DEL+16)
#define CMD_EXEC (CMD_TOUCH+24)
#define CMD_LOU (CMD_EXEC+20)
#define HEX (CMD_LOU+16)
#define CHAR_DEVICE (HEX+64)
#define KEYF0IN		(CHAR_DEVICE + 8)
#define CAPSON 		(KEYF0IN + 4)
// key code
#define BACK_SPACE 	0x08
#define ENTER 		0x0d
#define CAPSLOCK   	0x14
// file operations
#define FILE_IDLE 0
#define FILE_READ 14
#define FILE_WRITE 15
#define FILE_NORMAL 0
#define FILE_ERROR 1
#define FILE_EOF 2
#define FILE_MODE_BINARY 0
#define FILE_MODE_CHAR 1
#define FILE_MODE_IN 2
#define FILE_MODE_OUT 4
// disk address
#define CATALOG_OFFSET 159
#define DATA_OFFSET 191
#define BLOCK_SIZE 512
// constant
#define TRUE 1
#define FALSE 0
#define TEXT_HEIGHT 24
#define TEXT_WIDTH 40

typedef int BOOL;

typedef struct{
	unsigned short current_sector;
	unsigned short read_write_head;
	unsigned int size;
}FileInfo;

typedef struct{
	char name[8];
	char extension[3];
	unsigned char nature;
	char reserved[10];
	unsigned short time;
	unsigned short date;
	unsigned short starting_sector;
	unsigned int size;
}CatalogItem;

unsigned int* console;
unsigned int* error;
unsigned int* cmd_dir;
unsigned int* cmd_type;
unsigned int* cmd_rename;
unsigned int* cmd_exit;
unsigned int* cmd_del;
unsigned int* cmd_touch;
unsigned int* cmd_exec;
unsigned int* cmd_lou;
unsigned int* hex;
FileInfo* file_info;

void Initial()
{
	unsigned int* address;
	// initial VRAM
	// address = (unsigned int*)VRAM;
	// *address = 0;

	// initial KB_BUFFER
	address = (unsigned int*)KB_BUFFER;
	*address = 0;

	// initial CHAR_DEVICE
	address = (unsigned int*)CHAR_DEVICE;
	*address = 0;
	*(address+1) = 0;

	address = (unsigned int *) KEYF0IN;
	*address = 0;


	// initial global variable
	// *(int* ) POINTER=0;
	//enable Int
	asm ("addi 	$t0,	$zero,	0xff");
	asm ("mtc0	$t0,	$11"); 


	hex = (unsigned int*)HEX;
	
	hex[0]='0'+0x700;hex[1]='1'+0x700;hex[2]='2'+0x700;hex[3]='3'+0x700;
	hex[4]='4'+0x700;hex[5]='5'+0x700;hex[6]='6'+0x700;hex[7]='7'+0x700;
	hex[8]='8'+0x700;hex[9]='9'+0x700;hex[10]='a'+0x700;hex[11]='b'+0x700;
	hex[12]='c'+0x700;hex[13]='d'+0x700;hex[14]='e'+0x700;hex[15]='f'+0x700;


	console = (unsigned int*)CONSOLE;
	console[0] = 'C' + 0x700 ; console[1] = 'o' + 0x700 ; console[2] = 'n' + 0x700 ; console[3] = 's' + 0x700 ; console[4] = 'o' + 0x700 ;
	console[5] = 'l' + 0x700 ; console[6] = 'e' + 0x700 ; console[7] = '>' + 0x700 ; console[8] = '>' + 0x700 ; console[9] = 0;

	error = (unsigned int*)ERROR;
	error[0] = 'E' + 0x700 ; error[1] = 'r' + 0x700 ; error[2] = 'r' + 0x700 ; error[3] = 'o' + 0x700 ;
	error[4] = 'r' + 0x700 ; error[5] = '!' + 0x700 ; error[6] = '\0';

	cmd_dir = (unsigned int*)CMD_DIR;
	cmd_dir[0] = 'd'  ; cmd_dir[1] = 'i'  ; cmd_dir[2] = 'r'  ; cmd_dir[3] = '\0'; 

	cmd_type = (unsigned int*)CMD_TYPE;
	cmd_type[0] = 't'  ; cmd_type[1] = 'y'  ; cmd_type[2] = 'p'  ; cmd_type[3] = 'e'  ; cmd_type[4] = '\0';

	cmd_rename = (unsigned int*)CMD_RENAME;
	cmd_rename[0] = 'r'  ; cmd_rename[1] = 'e'  ; cmd_rename[2] = 'n'  ; cmd_rename[3] = '\0';

	cmd_exit = (unsigned int*)CMD_EXIT;
	cmd_exit[0] = 'e'  ; cmd_exit[1] = 'x'  ; cmd_exit[2] = 'i'  ; cmd_exit[3] = 't'  ; cmd_exit[4] = '\0';

	cmd_del = (unsigned int*)CMD_DEL;
	cmd_del[0] = 'd'  ; cmd_del[1] = 'e'  ; cmd_del[2] = 'l'  ; cmd_del[3] = '\0';

	cmd_touch = (unsigned int*)CMD_TOUCH;
	cmd_touch[0] = 't'  ; cmd_touch[1] = 'o'  ; cmd_touch[2] = 'u'  ; cmd_touch[3] = 'c'  ; cmd_touch[4] = 'h'  ; cmd_touch[5] = '\0';

	cmd_exec = (unsigned int*)CMD_EXEC;
	cmd_exec[0] = 'e'  ; cmd_exec[1] = 'x'  ; cmd_exec[2] = 'e'  ; cmd_exec[3] = 'c'  ; cmd_exec[4] = '\0';

	cmd_lou = (unsigned int*)CMD_LOU;
	cmd_lou[0] = 'l'  ; cmd_lou[1] = 'o'  ; cmd_lou[2] = 'u'  ; cmd_lou[3] = '\0'; 

	file_info = (FileInfo*)FILE_INFO;
}

void Strcpy(unsigned int* dest, unsigned int* src, unsigned int size)
{
	int i=0;
	while (i<size) {
		dest[i] = src[i];
		i++;
	}
}

void CharToInt(unsigned int* src, unsigned int* dest, unsigned int size) 
{
	unsigned int count=0;
	while (1) {
		asm ("andi $t0, %0, 0x000000ff"::"r"(src[count>>2]));
		asm ("add %0, $t0, $zero":"=r"(dest[count]));
		//dest[count] = src[count>>2]&0x000000ff;
		if (dest[count] == '\0') {
			break;
		}
		count++;
		asm ("srl $t0, %0, 8"::"r"(src[count>>2]));
		asm ("andi $t0, $t0, 0xff");
		asm ("add %0, $t0, $zero":"=r"(dest[count]));
		//dest[count] = (src[count>>2]&0x0000ff00)>>8;
		if (dest[count] == '\0') {
			break;
		}
		count++;
		asm ("srl $t0, %0, 16"::"r"(src[count>>2]));
		asm ("andi $t0, $t0, 0xff");
		asm ("add %0, $t0, $zero":"=r"(dest[count]));
		//dest[count] = (src[count>>2]&0x00ff0000)>>16;
		if (dest[count] == '\0') {
			break;
		}
		count++;
		asm ("srl $t0, %0, 24"::"r"(src[count>>2]));
		asm ("andi $t0, $t0, 0xff");
		asm ("add %0, $t0, $zero":"=r"(dest[count]));
		//dest[count] = (src[count>>2]&0xff000000)>>24;
		if (dest[count] == '\0') {
			break;
		}
		count++;
		if (count >= size) {
			break;
		}
	}
}

void IntToChar(unsigned int* src, unsigned int* dest, unsigned int size) 
{
	unsigned int count=0;
	while (1) {
		dest[count>>2] = 0;
		dest[count>>2] += src[count];
		if (src[count] == '\0') {
			break;
		}
		count++;
		dest[count>>2] += src[count]<<8;
		if (src[count] == '\0') {
			break;
		}
		count++;
		dest[count>>2] += src[count]<<16;
		if (src[count] == '\0') {
			break;
		}
		count++;
		dest[count>>2] += src[count]<<24;
		if (src[count] == '\0') {
			break;
		}
		count++;
		if (count >= size) {
			break;
		}
	}

}

BOOL Strcmp(const unsigned int* s1, const unsigned int* s2, unsigned int size)
{
	unsigned int i;
	unsigned int c1, c2;

	for (i=0; i<size; i++) {
		c1 = s1[i] & 0xff;
		c2 = s2[i] & 0xff;
		if (c1=='\0' && c2=='\0') {
			return TRUE;
		}
		else if (c1=='\0' && c2!='\0') {
			return FALSE;
		}
		else if (c1!='\0' && c2=='\0') {
			return FALSE;
		}
		else if (c1-c2 != 0) {
			return FALSE;
		}
	}
	return TRUE;
}

unsigned int Multiply(unsigned int a, unsigned int b)
{
	volatile unsigned int i=0;
	volatile unsigned int result = 0;
	while (i<b){
		result += a;
		i++;
	}
// 	for (i=0; i<b; i++) {
// 		result += a;
// 	}
 	return result;
}

unsigned int Divide(unsigned int dividend, unsigned divider)
{
	int i=0;
	while (dividend >= divider) {
		dividend -= divider;
		i++;
	}
	return i;
}

unsigned int Mod(unsigned int dividend, unsigned divider)
{
	while (dividend >= divider) {
		dividend -= divider;
	}
	return dividend;
}


void Sleep(unsigned int num){
	while (num--){
		asm("nop");
	}
}

unsigned int ReadChar()
{
	unsigned int a0;
	asm ("addiu $sp, $sp, -4");
	asm ("sw $ra, 0($sp)");

	asm ("add $v0, $zero, 12");
	asm ("syscall");
	asm ("add %0, $zero, $a0":"=r"(a0));
/*
	if (a0 == 0x1f0){
		do{
			asm ("add $v0, $zero, 12");
			asm("syscall");
			Sleep(10);
			asm ("add %0, $zero, $a0":"=r"(a0));
		} while(a0 != 0);
		asm ("lw $ra, 0($sp)");
		asm ("addiu $sp, $sp, 4");
		return 0x100;
	}
*/		
	asm ("lw $ra, 0($sp)");
	asm ("addiu $sp, $sp, 4");
	return a0;
}

void PrintChar(unsigned int c, unsigned int color)
{
	c &= 0xff;
	c += color;

	asm ("addiu $sp, $sp, -4");
	asm ("sw $ra, 0($sp)");

	asm ("add $a0, $zero, %0"::"r"(c));
	asm ("add $v0, $zero, 11");
	asm ("syscall");

	asm ("lw $ra, 0($sp)");
	asm ("addiu $sp, $sp, 4");
}

void PrintString(unsigned int* str, unsigned int color)
{
	int i;

	for (i=0; str[i] != '\0'; i++){
		str[i] &= 0xff;
		str[i] += color;
	}
	asm ("addiu $sp, $sp, -4");
	asm ("sw $ra, 0($sp)");

	asm ("add $a0, $zero, %0"::"r"(str));
	asm ("add $v0, $zero, 4");
	asm ("syscall");

	asm ("lw $ra, 0($sp)");
	asm ("addiu $sp, $sp, 4");
}

void PrintInt(unsigned int i)
{
	asm ("addiu $sp, $sp, -4");
	asm ("sw $ra, 0($sp)");

	asm ("add $a0, $zero, %0"::"r"(i));
	asm ("add $v0, $zero, 1");
	asm ("syscall");

	asm ("lw $ra, 0($sp)");
	asm ("addiu $sp, $sp, 4");
}


// split file_name to name and extension
void SplitName(unsigned int* file_name, unsigned int* name, unsigned int* extension)
{
	unsigned int i, j;
	//unsigned int file_name[12];
	//CharToInt(old_file_name, file_name);

	for (i=0; i<8; i++) {
		if (file_name[i] == '.') {
			name[i] = '\0';
			break;
		}
		name[i] = file_name[i];
	}
	i++;
	for (j=0; j<3; j++) {
		extension[j] = file_name[i];
		if (file_name[i] == '\0') {
			break;
		}
		i++;
	}
}

void SectionRead(unsigned int section_number)
{
	asm ("addiu $sp, $sp, -4");
	asm ("sw $ra, 0($sp)");

	asm ("add $a0, $zero, %0"::"r"(section_number));
	asm ("add $a1, $zero, $zero");
	asm ("add $v0, $zero, 14");
	asm ("syscall");

	asm ("lw $ra, 0($sp)");
	asm ("addiu $sp, $sp, 4");
}

void SectionWrite(unsigned int section_number)
{
	asm ("addiu $sp, $sp, -4");
	asm ("sw $ra, 0($sp)");

	asm ("add $a0, $zero, %0"::"r"(section_number));
	asm ("add $a1, $zero, $zero");
	asm ("add $v0, $zero, 15");
	asm ("syscall");

	asm ("lw $ra, 0($sp)");
	asm ("addiu $sp, $sp, 4");
}

void ClearScreen()
{
	unsigned int i;
	unsigned int* char_device = (unsigned int*)CHAR_DEVICE;
	unsigned int* gpio = (unsigned int*)GPIO;

	*char_device = 0;
	*(char_device+1) = 0;
	
	asm ("sll $t0, %0, 16"::"r"(*char_device));
	asm ("sll $t1, %0, 10"::"r"(*(char_device+1)));
	asm ("add $t0, $t0, $t1");
	asm ("sw $t0, 0(%0)"::"r"(gpio));

	for (i=0; i<1200; i++) {
		PrintChar(' ', 0);
	}

	*char_device = 0;
	*(char_device+1) = 0;
	
	asm ("sll $t0, %0, 16"::"r"(*char_device));
	asm ("sll $t1, %0, 10"::"r"(*(char_device+1)));
	asm ("add $t0, $t0, $t1");
	asm ("sw $t0, 0(%0)"::"r"(gpio));
}

void OpenFile(unsigned int* file_name, unsigned int flag, unsigned int mode)
{
	CatalogItem* item;
	unsigned int name[9], extension[4];
	unsigned int item_name[9], item_extension[4];
	unsigned int i,j;
	int current_sector, next_sector;

	SplitName(file_name, name, extension);
	// search in catalog
	for (i=0; i<32; i++) {
		SectionRead(CATALOG_OFFSET+i);
		item = (CatalogItem*)FILE_BUFFER;
		for (j=0; j<16; j++) {
			CharToInt((unsigned int*)item, item_name, 8);
			CharToInt((unsigned int*)item+2, item_extension, 4);
			if (Strcmp(item_name, name, 8)==TRUE 
				&& Strcmp(item_extension, extension, 3)==TRUE) {
				break;
			}
			else {
				item++;
			}
		}
		if (j != 16) {
			break;
		}
	}
	// if cannot find the file
	if (i == 32) {
		PrintString(error, 0x400);
		PrintChar(ENTER, 0x700);
		file_info->current_sector = 0xff;
		file_info->read_write_head = 0;
		file_info->size = 0;
		return;
	}
	else {
		// set file_info
		file_info->current_sector = item->starting_sector;
		file_info->read_write_head = 0;
		file_info->size = item->size;
		// read file
		SectionRead(DATA_OFFSET+file_info->current_sector-2);
	}
}

// length must less than 512
//void ReadFile(char* buffer, unsigned int length)
//{
//	int i;
//	char* file = (char*)FILE_BUFFER;
//	unsigned int fat_sector;
//	unsigned short next_sector;
//	unsigned int sum_of_sectors;
//
//	// the last sector
//	if (file_info->read_write_head+length > file_info->size) {
//		length = file_info->size - file_info->read_write_head;
//		for (i=0; i<length; i++) {
//			buffer[i] = file[file_info->read_write_head++];
//		}
//	}
//	// cross sectors
//	else if (file_info->read_write_head+length > 512) {
//		length -= 512 - file_info->read_write_head;
//		for (i=0; file_info->read_write_head<512; i++) {
//			buffer[i] = file[file_info->read_write_head++];
//		}
//		fat_sector = file_info->current_sector >> 8; 
//		// read FAT
//		SectionRead(fat_sector+1);
//		next_sector = *(unsigned short*)(file+((file_info->current_sector&0xff)<<1)); 
//		// read file
//		SectionRead(DATA_OFFSET+next_sector-2);
//		file_info->current_sector = next_sector;
//		file_info->read_write_head = 0;
//		file_info->size -= 512;
//		for (; length>0; length--) {
//			buffer[i] = file[file_info->read_write_head];
//			file_info->read_write_head++;
//			i++;
//		}
//	}
//	// simple case
//	else {
//		for (i=0; i<length; i++) {
//			buffer[i] = file[file_info->read_write_head++];
//		}
//	}
//}

//void ClearScreen()
//{
//	char* VRAM = (char*)VRAM;
//	unsigned int i, j;
//	
//	*char_device = 0;
//	*(char_device+1) = 0;
//	for (i=0; i<TEXT_HEIGHT; i++) {
//		for (j=0; j<TEXT_WIDTH; j++) {
//			PrintChar(20);
//		}
//	}
//	*char_device = 0;
//	*(char_device+1) = 0;
//}

void Dir()
{
	CatalogItem* item;
	unsigned int item_name[9], item_extension[4];
	unsigned int empty[1];
	empty[0] = 0;
	
	int i,j;
	// search in catalog
	for (i=0; i<32; i++) {
		SectionRead(CATALOG_OFFSET+i);
		item = (CatalogItem*)FILE_BUFFER;
		for (j=0; j<16; j++) {
			CharToInt((unsigned int*)item, item_name, 8);
			CharToInt((unsigned int*)item+2, item_extension, 4);
			if (Strcmp(item_name, empty, 8)==FALSE) {
				item_name[8] = '\0';
				item_extension[3] = '\0';
				PrintString(item_name, 0x200);
				PrintChar('.', 0x200);
				PrintString(item_extension, 0x200);
				PrintChar(ENTER, 0x700);
			}
			item++;
		}
	}
}

void Type(unsigned int* argv[])
{
	int i, j;
	char* file = (char*)FILE_BUFFER;
	unsigned int sum_sectors;
	unsigned short fat_sector, next_sector;
	unsigned int offset;

	OpenFile(argv[1], 0, 0);

	sum_sectors = (file_info->size >> 9) + 1;

	for (i=0; i<sum_sectors; i++) {
		if (i == sum_sectors-1) {
			for (j=0; j<file_info->size; j++) {
				PrintChar(*(unsigned int*)(file+(j>>2)), 0x700);
				//PrintChar(file[j]);
			}
		}
		else {
			for (j=0; j<512; j++) {
				PrintChar(*(unsigned int*)(file+(j>>2)), 0x700);
				//PrintChar(file[j]);
			}
			fat_sector = file_info->current_sector >> 8; // divide by 256
			// read FAT
			SectionRead(fat_sector+1);
			asm ("andi $t0, %0, 0xff"::"r"(file_info->current_sector));
			asm ("sll %0, $t0, 1":"=r"(offset));
			next_sector = *(unsigned short*)(file+offset);
			//next_sector = *(unsigned short*)(file+((file_info->current_sector&0xff)<<1));
			// read file
			SectionRead(DATA_OFFSET+next_sector-2);
			file_info->current_sector = next_sector;
			file_info->read_write_head = 0;
		}
	}
	PrintChar(ENTER, 0x700);
}

void Rename(unsigned int* argv[])
{
	CatalogItem* item;

	unsigned int name[9], extension[4];
	unsigned int item_name[9], item_extension[4];
	unsigned int new_name[9], new_extension[4];
	unsigned int new_item_name[2], new_item_extension[1];
	unsigned int i,j;

	SplitName(argv[1], name, extension);
	SplitName(argv[2], new_name, new_extension);
	// search in catalog
	for (i=0; i<32; i++) {
		SectionRead(CATALOG_OFFSET+i);
		item = (CatalogItem*)FILE_BUFFER;
		for (j=0; j<16; j++) {
			CharToInt((unsigned int*)item, item_name, 8);
			CharToInt((unsigned int*)item+2, item_extension, 4);
			if (Strcmp(item_name, name, 8)==TRUE 
				&& Strcmp(item_extension, extension, 3)==TRUE) {

				IntToChar(new_name, new_item_name, 8);
				IntToChar(new_extension, new_item_extension, 8);

				*(unsigned int*)item = new_item_name[0];
				*((unsigned int*)item+1) = new_item_name[1];
				*((unsigned int*)item+2) = new_item_extension[0];

				SectionWrite(CATALOG_OFFSET+i);
				return;
			}
			else {
				item++;
			}
		}
	}
	// if cannot find the file
	if (i == 32) {
		PrintString(error, 0x400);
		PrintChar(ENTER, 0x700);
		file_info->current_sector = 0;
		file_info->read_write_head = 0;
		file_info->size = 0;
		return;
	}
}

void Touch(unsigned int* argv[])
{
	CatalogItem* item;
	unsigned int name[9], extension[4];
	unsigned int item_name[9];
	unsigned int new_item_name[2], new_item_extension[1];
	unsigned int empty[0];
	unsigned int i,j;
	unsigned short sector_number;
	char* file = (char*)FILE_BUFFER;
	
	empty[0] = '\0';

	SplitName(argv[1], name, extension);
	// read FAT
	for (i=0; i<79; i++) {
		SectionRead(1+i);
		for (j=0; j<512; j+=2) {
			sector_number = *(unsigned short*)(file+j);
			if (sector_number == 0) {
				*(unsigned short*)(file+j) = 0xffff;
				sector_number = (i<<8) + (j>>1);
				// write 2 FAT
				SectionWrite(1+i);
				SectionWrite(80+i);
				goto out;
			}
		}
	}
out:
	// search in catalog
	for (i=0; i<32; i++) {
		SectionRead(CATALOG_OFFSET+i);
		item = (CatalogItem*)FILE_BUFFER;
		for (j=0; j<16; j++) {
			CharToInt((unsigned int*)item, item_name, 8);
			if (Strcmp(item_name, empty, 8)==TRUE) {
				IntToChar(name, new_item_name, 8);
				IntToChar(extension, new_item_extension, 4);

				*(unsigned int*)item = new_item_name[0];
				*((unsigned int*)item+1) = new_item_name[1];
				*((unsigned int*)item+2) = new_item_extension[0];
				
				item->size = 0;
				item->starting_sector = sector_number;
				SectionWrite(CATALOG_OFFSET+i);

				return;
			}
			else {
				item++;
			}
		}
	}
}

void Del(unsigned int* argv[]) 
{
	CatalogItem* item;
	unsigned int name[9], extension[4];
	unsigned int item_name[9], item_extension[4];
	unsigned int i,j, offset;
	unsigned short next_sector;
	char* file = (char*)FILE_BUFFER;

	SplitName(argv[1], name, extension);
	// search in catalog
	for (i=0; i<32; i++) {
		SectionRead(CATALOG_OFFSET+i);
		item = (CatalogItem*)FILE_BUFFER;
		for (j=0; j<16; j++) {
			CharToInt((unsigned int*)item, item_name, 8);
			CharToInt((unsigned int*)item+2, item_extension, 4);
			if (Strcmp(item_name, name, 8)==TRUE 
				&& Strcmp(item_extension, extension, 3)==TRUE) {

				*(unsigned int*)item = 0;
				*((unsigned int*)item+1) = 0;
				*((unsigned int*)item+2) = 0;

				item->size = 0;
				file_info->current_sector = item->starting_sector;
				SectionWrite(CATALOG_OFFSET+i);
				goto clear;
			}
			else {
				item++;
			}
		}
	}
	// if cannot find the file
	if (i == 32) {
		PrintString(error, 0x400);
		PrintChar(ENTER, 0x700);
		file_info->current_sector = 0;
		file_info->read_write_head = 0;
		file_info->size = 0;
		return;
	}
	// clear FAT
clear:
	do {
		SectionRead(1+(file_info->current_sector>>8));

		asm ("andi $t0, %0, 0xff"::"r"(file_info->current_sector));
		asm ("sll %0, $t0, 1":"=r"(offset));

		next_sector = *(unsigned short*)(file+offset);
		*(unsigned short*)(file+offset) = 0;
		//next_sector = *(unsigned short*)(file+((file_info->current_sector&0xff)<<1));
		//*(unsigned short*)(file+((file_info->current_sector&0xff)<<1)) = 0;
		SectionWrite(1+(file_info->current_sector>>8));
		SectionWrite(80+(file_info->current_sector>>8));
		file_info->current_sector = next_sector;
	}
	while (next_sector != 0xffff);
}

//BOOL PutDown(char c)
//{
//	char* char_device = (char*)VRAM;
//	char current_c;
//	current_c = *(char_device+Multiply(TEXT_WIDTH,*(char_device))+*(char_device+1)+2);
//	if (current_c == 'x' || current_c == 'o') {
//		return FALSE;
//	}
//	else {
//		PrintChar(c);
//		if (*(char_device+1) == 0) {
//			*(char_device+1) = TEXT_WIDTH - 1;
//			(*char_device)--;
//		}
//		else {
//			(*(char_device+1))--;
//		}
//		return TRUE;
//	}
//}
//
//BOOL CheckWin(char current)
//{
//	char* char_device = (char*)VRAM;
//	unsigned int i, j, count, result, raw, col, dot;
//
//	raw = *char_device;
//	col = *(char_device+1);
//	// check four directions in turn
//	// 0 degree
//	count = 1;
//	dot = Multiply(TEXT_WIDTH, raw) + col;
//	for (i=1; i<=4; i++) {
//		if (col >= i 
//			&& *(char_device+2+dot-i) == current) {
//			count++;
//			if (count == 5) {
//				return TRUE;
//			}
//		}
//		else {
//			break;
//		}
//	}
//	for (i=1; i<=4; i++) {
//		if (col+i <= TEXT_WIDTH-1
//			&& *(char_device+2+dot+i) == current) {
//			count++;
//			if (count == 5) {
//				return TRUE;
//			}
//		}
//		else {
//			break;
//		}
//	}
//	// 90 degree
//	count = 1;
//	for (i=1; i<=4; i++) {
//		dot -= TEXT_WIDTH;
//		if (raw >= i
//			&& *(char_device+2+dot) == current) {
//			count++;
//			if (count == 5) {
//				return TRUE;
//			}
//		}
//		else {
//			break;
//		}
//	}
//	dot = Multiply(TEXT_WIDTH, raw) + col;
//	for (i=1; i<=4; i++) {
//		dot += TEXT_WIDTH;
//		if (raw+i <= TEXT_HEIGHT-1
//			&& *(char_device+2+dot) == current) {
//			count++;
//			if (count == 5) {
//				return TRUE;
//			}
//		}
//		else {
//			break;
//		}
//	}
//	return FALSE;
//}
//
//void Exec(char* argv[])
//{
//	char c;
//	char* char_device = (char*)VRAM;
//	int flag = 0;
//	unsigned int i, j, result;
//	char xWin[6];
//	xWin[0] = 'x' + 0x700 ; xWin[1] = ' ' + 0x700 ; xWin[2] = 'w' + 0x700 ; xWin[3] = 'i' + 0x700 ; xWin[4] = 'n' + 0x700 ; xWin[5] = '\0';
//	char oWin[6];
//	oWin[0] = 'o' + 0x700 ; xWin[1] = ' ' + 0x700 ; xWin[2] = 'w' + 0x700 ; xWin[3] = 'i' + 0x700 ; xWin[4] = 'n' + 0x700 ; xWin[5] = '\0';
//
//	ClearScreen();
//	*char_device = TEXT_HEIGHT>>1;
//	*(char_device+1) = TEXT_WIDTH>>1;
//	while (1) {
//		while (1) {
//			c = ReadChar();
//			if (c != '\0') {
//				break;
//			}
//		}
//		switch (c) {
//		case 'x':
//			if (flag == 1) {
//				break;
//			}
//			if (PutDown('x') == TRUE) { 
//				flag = 1;
//				if (CheckWin('x') == TRUE) {
//					ClearScreen();
//					*char_device = TEXT_HEIGHT>>1;
//					*(char_device+1) = (TEXT_WIDTH>>1)-2;
//					PrintString(xWin);
//					while (1) {
//						c = ReadChar();
//						if (c == ENTER) {
//							break;
//						}
//					}
//					ClearScreen();
//					return;
//				}
//			}
//			break;
//		case 'o':
//			if (flag == 0) {
//				break;
//			}
//			if (PutDown('o') == TRUE) {
//				flag = 0;
//				if (CheckWin('o') == TRUE) {
//					ClearScreen();
//					*char_device = TEXT_HEIGHT>>1;
//					*(char_device+1) = (TEXT_WIDTH>>1)-2;
//					PrintString(oWin);
//					while (1) {
//						c = ReadChar();
//						if (c == ENTER) {
//							break;
//						}
//					}
//					ClearScreen();
//					return;
//				}
//			}
//			break;
//		case ENTER:
//			*char_device = 0;
//			*(char_device+1) = 0;
//			for (i=0; i<TEXT_HEIGHT; i++) {
//				for (j=0; j<TEXT_WIDTH; j++) {
//					PrintChar(20);
//				}
//			}
//			*char_device = 0;
//			*(char_device+1) = 0;
//			return;
//		default:
//			break;
//		}
//	}
//}

void Lou()
{
	unsigned int s[23];
	s[0] = 0x780; s[1] = 's' + 0x700 ; s[2] = 'i' + 0x700 ; s[3] = 'r' + 0x700 ; s[4] = ',' + 0x700 ;
	s[5] = 0x7ab; s[6] = 0x7d0; s[7] = ' ' + 0x700 ; // 楼sir，你好
	s[8] = ENTER+0x700;
	s[9] = 0x784; s[10] = 0x785; s[11] = 0x786;// 魏世嘉
	s[12] = ' ';
	s[13] = 0x787; s[14] = 0x788;// 陈俊
	s[15] = ' ';
	s[16] = 0x789; s[17] = 0x788; s[18] = 0x78a;// 刘俊灏
	s[19] = ' ';
	s[20] = 0x78b; s[21] = 0x7f2;// 孙同
	s[22] = '\0';

	PrintString(s, 0x700);
	PrintChar(ENTER, 0x700);
}

//void Exit()
//{
//	volatile unsigned int* exit = 0;
//	*exit = 1;
//}

unsigned int getCode(unsigned int scanCode)
{
	/* 131 scanCode decode*/
	unsigned int DecodeBig[] = { 0x20, 		/* we do not have scan code as 0x00 */
		0x108, 	0x20,	0x104, 	0x102, 	0x100, 	0x101, 	0x10b, 	0x20, 	0x109, 	0x107,
		0x105, 	0x103, 	0x09, 	0x7e, 	0x20, 	0x20, 	0x121, 	0x115, 	0x20, 	0x116,
		0x71, 	0x21, 	0x20, 	0x20, 	0x20, 	0x7a, 	0x73, 	0x61, 	0x77, 	0x40,
		0x117,	0x20, 	0x63, 	0x78, 	0x64, 	0x65, 	0x24, 	0x23, 	0x117,	0x20,
		0x20, 	0x76, 	0x66, 	0x74, 	0x72, 	0x25, 	0x114, 	0x20, 	0x6e,	0x62,
		0x68, 	0x67, 	0x79,	0x5e, 	0x20, 	0x20, 	0x20, 	0x6d, 	0x6a,	0x75,
		0x26, 	0x2a, 	0x20, 	0x20,	0x3c, 	0x6b, 	0x69, 	0x6f,	0x29, 	0x28,
		0x20, 	0x20, 	0x3e, 	0x3f, 	0x6c,	0x3a, 	0x70, 	0x5f, 	0x20,	0x20,
		0x20, 	0x22, 	0x20, 	0x7b, 	0x2b, 	0x20,	0x20, 	0x14, 	0x115, 	0x0d,
		0x7d, 	0x20, 	0x7c, 	0x20, 	0x20, 	0x20, 	0x20,	0x20, 	0x20, 	0x20,
		0x20, 	0x08, 	0x20, 	0x20, 	0x119, 	0x20, 	0x10E, 	0x118, 	0x20, 	0x20,
		0x20, 	0x11C, 	0x2e, 	0x10D, 	0x10F, 	0x20, 	0x10C, 	0x1b, 	0x120,	0x10A,
		0x2b, 	0x111, 	0x2d, 	0x2a, 	0x110, 	0x20, 	0x20, 	0x20, 	0x20, 	0x20,
		0x106
	};

	unsigned int DecodeLittle[] = { 0x20, 	/* we do not have scan code as 0x00 */
		0x108, 	0x20,	0x104, 	0x102, 	0x100, 	0x101, 	0x10b, 	0x20, 	0x109, 	0x107,
		0x105, 	0x103, 	0x09, 	0x60, 	0x20, 	0x20, 	0x121, 	0x115, 	0x20, 	0x116,
		0x71, 	0x31, 	0x20, 	0x20, 	0x20, 	0x7a, 	0x73, 	0x61, 	0x77, 	0x32,
		0x117,	0x20, 	0x63, 	0x78, 	0x64, 	0x65, 	0x34, 	0x33, 	0x117,	0x20,
		0x20, 	0x76, 	0x66, 	0x74, 	0x72, 	0x35, 	0x114, 	0x20, 	0x6e,	0x62,
		0x68, 	0x67, 	0x79,	0x36, 	0x20, 	0x20, 	0x20, 	0x6d, 	0x6a,	0x75,
		0x37, 	0x38, 	0x20, 	0x20,	0x2c, 	0x6b, 	0x69, 	0x6f,	0x30, 	0x39,
		0x20, 	0x20, 	0x2e, 	0x2f, 	0x6c,	0x3b, 	0x70, 	0x2d, 	0x20,	0x20,
		0x20, 	0x27, 	0x20, 	0x5b, 	0x3d, 	0x20,	0x20, 	0x14, 	0x115, 	0x0d,
		0x5d, 	0x20, 	0x5c, 	0x20, 	0x20, 	0x20, 	0x20,	0x20, 	0x20, 	0x20,
		0x20, 	0x08, 	0x20, 	0x20, 	0x119, 	0x20, 	0x10E, 	0x118, 	0x20, 	0x20,
		0x20, 	0x11C, 	0x2e, 	0x10D, 	0x10F, 	0x20, 	0x10C, 	0x1b, 	0x120,	0x10A,
		0x2b, 	0x111, 	0x2d, 	0x2a, 	0x110, 	0x20, 	0x20, 	0x20, 	0x20, 	0x20,
		0x106
	};


	if (scanCode > 0x100 && scanCode <= 0x183){
		if (!(*(unsigned int *)CAPSON)){
			return DecodeBig[scanCode - 0x100];		
		}
		else
			return DecodeLittle[scanCode - 0x100];	 			
	}
	else return 0x00;
}

void ReadLine(unsigned int* line)
{
	unsigned int c, ch;
	unsigned int count = 0;
	unsigned int lineLimit[] = {'T' + 0x700, 'o' + 0x700, 'o' + 0x700, ' ' + 0x700, 
							'L' + 0x700, 'o' + 0x700, 'n' + 0x700, 'g' + 0x700, '!' + 0x700, '\0'};
	while (1) {
		c = ReadChar();				// ScanCode
		if (c == 0x1e0) continue;
		ch = getCode(c);
		if ( ch != 0xf0 ){
			switch (ch) {
				case '\0':
					break;
				case CAPSLOCK:
					// asm ("syscall");
					// asm ("syscall");
					// asm ("syscall");
					PrintInt(*(unsigned int *)CAPSON);
					*(unsigned int *)CAPSON = !*(unsigned int *)CAPSON;
					PrintInt(*(unsigned int *)CAPSON);
					// asm ("syscall");
					// asm ("syscall");
					// asm ("syscall");
					break; 
				case ENTER:
					line[count] = '\0';
					PrintChar(ENTER, 0x400);
					return;
					break;
				case BACK_SPACE:
					// PrintInt(count);
					if (count > 0) {
						line[--count] = '\0';
						// PrintInt(count);	
						PrintChar(BACK_SPACE, 0);	
						 //asm ("syscall");
					}
					break;
					// asm ("syscall");
				default:
					PrintChar(ch, 0x700);
					if (ch >= 20 && ch <= 0xfe) {
						line[count++] = ch;
					}
					break;
			}	
		}
		
		// command buffer is full
		if (count == 25) {
			line[0] = '\0';
			PrintChar(ENTER, 0x700);
			PrintString(lineLimit, 0x400);
			PrintChar(ENTER, 0x700);
			return;
		}
	}
}

void GetParameter(unsigned int* command, int* argc, unsigned int** argv)
{
	int i;
	int flag = 0;

	*argc = 0;	
	for (i=0;;i++) {
		if (*argc == 3) {
			break;
		}
		if (flag == 0) {
			if (command[i] != ' ') {
				flag = 1;
				argv[*argc] = command+i;
				(*argc)++;
			}
			else {
				continue;
			}
		}
		else {
			if (command[i]==' ' || command[i]=='\0') {
				command[i] = '\0';
				flag = 0;
			}
			else {
				continue;
			}
		}
	}
}

void Execute(unsigned int argc, unsigned int* argv[])
{
	int i;
	unsigned int cmd_clr[] = {'c', 'l', 'r', '\0'};

	// for (i =0 ;i<argc; i++){
	// 	PrintChar(ENTER);
	// 	PrintString(argv[i]);
	// 	PrintChar('W' + 0x700);
	// 	PrintChar(ENTER);
	// }

	if (Strcmp(argv[0], cmd_dir, 4) == TRUE) {
		Dir();
	}
	else if (Strcmp(argv[0], cmd_type, 5) == TRUE) {
		Type(argv);
	}
	else if (Strcmp(argv[0], cmd_rename, 4) == TRUE) {
		Rename(argv);
	}
	else if (Strcmp(argv[0], cmd_del, 4) == TRUE) {
		Del(argv);
	}
	else if (Strcmp(argv[0], cmd_touch, 6) == TRUE) {
		Touch(argv);
	}
	else if (Strcmp(argv[0], cmd_clr, 4) == TRUE) {
		ClearScreen();
	}
//	else if (Strcmp(argv[0], cmd_exec, 5) == TRUE) {
//		Exec(argv);
//	}
//	else if (Strcmp(argv[0], cmd_exit, 5) == TRUE) {
//		Exit();
//	}
	else if (Strcmp(argv[0], cmd_lou, 4) == TRUE) {
		Lou();
	}
	else {
		PrintString(error, 0x400);
		PrintChar(ENTER, 0x700);
	}
}

int main()
{
	asm ("addiu $sp, $zero, 0x3f68");
	unsigned int command[25];
	int i;
	int argc;
	unsigned int* argv[3];

	Initial();
	
	while (1) {
		for (i=0; i<25; i++) {
			command[i] = '\0';
		}
		PrintString(console, 0x200);
		ReadLine(command);
		// PrintString(command);
		// PrintChar('E' + 0x700);
		// PrintChar(ENTER);
		GetParameter(command, &argc, argv);
		Execute(argc, argv);
	}
	
	return 0;
}
