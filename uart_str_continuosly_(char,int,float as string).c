#include<reg51.h>

int main(){
	unsigned char s1[] = "SAKTHIVEL";
	unsigned char s2[] = "12345";
	unsigned char s3[] = "1.25";
	
	unsigned int i=0;
	TMOD = 0x20; // tmier 1 mode 2
	TH1 = 0xff; // 9600 baud rate
	SCON = 0x50;  // mode 1 , ren enabled 
	TR1 = 1;
	while(1){
		i = 0;
		
		// sending string
	while(s1[i] != '\0'){
		SBUF = s1[i++];
		while(TI == 0);
		TI = 0;
	}
	SBUF = '\n';
	while(TI ==0);
	TI = 0;
	
	// sending integer as string
	i=0;
	while(s2[i] != '\0'){
		SBUF = s2[i++];
		while(TI == 0);
		TI = 0;
	}
	SBUF = '\n';
	while(TI ==0);
	TI = 0;
	
	//sending float as string
	i=0;
	while(s3[i] != '\0'){
		SBUF = s3[i++];
		while(TI == 0);
		TI = 0;
	}
	SBUF = '\n';  
	while(TI ==0);
	TI = 0;	
}


}