/*Ini adalah proses mengimplementasikan konjektur Collatz ke shared memory
John Wiley & Sons, 2013*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>

int main(int argc, char *argv[])
{
 const int SIZE = 4096; 		/*ukuran objek shared memory dalam bytes*/
 const char *name = "COLLATZ";	 /*nama dari objek shared memory*/

 int shm_fd;				/*pendeskripsi file shared memory*/
 void *ptr;				/*pointer ke objek shared memory*/
 char str[128];
 int n = atoi(argv[1]);

/*buat segmen shared memory */
 shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666); 			

/* konfigurasi ukuran size dari segmen shared memory*/
 ftruncate(shm_fd,SIZE);  							

 /* map segmen shared memory di alamat proses */
 ptr = mmap(0,SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
 if (ptr == MAP_FAILED) {
  printf("Map failed\n");
  exit(-1);
 }
 
 /*Tulis collatz sequence ke bagian shared memory, dan kita perlu melakukan penambahan nilai dari pointer setiap setelah melakukan write */

 sprintf(str,"%d, ", n);
 sprintf(ptr,"%s",str);
 while (n != 1) {
  ptr += strlen(str);

  if (n % 2 == 0)
   n = n / 2;
  else
   n = 3 * n + 1;

  sprintf(str,"%d, ", n);
  sprintf(ptr,"%s",str);
 }

 return 0;
}





