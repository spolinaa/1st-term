/* Buffer overflow
by Sokolova Polina */

#include <stdio.h> 
#include <string.h> 

void f1(char string[]) { 
char buffer[4]; 
strcpy(buffer, string); 
}   
void f2() { 
printf("\nBuffer Overflow!\n"); 
} 
int main(void) { 
	char string[] = "aaaaaaaa"      
 		        "\x19\x10\x40\x00";     
 	printf("f2: 0x%x\n", f2);  
 	f1(string); 
 	return 0; 
}
