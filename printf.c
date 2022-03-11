#include <unistd.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

static int write_stdout(const char *token, int length)
{
	int rc;
	int bytes_written = 0;

	do {
		rc = write(1, token + bytes_written, length - bytes_written);
		if (rc < 0)
			return rc;

		bytes_written += rc;
	} while (bytes_written < length);

	return bytes_written;
}

int iocla_printf(const char *format, ...)
{
	int long intreg, hexa;
	int farasemn;
	int bin[31],hex[7];
	int l, i = 0, j = 0, nr, r, p, k = 1;
	unsigned int u;
	int counter = 0, sr;
	
	char caracter, *string;
	char sir[1000];
	char lit[]="abcdef";
	//Implementez variabilele de care am nevoi in program

	char *c;
    c = (char *)calloc(1000, sizeof(char *));
    //Aloc dinamic memoria pt vectorul de caractere
    
    va_list ap;
    va_start(ap, format);
    //Implementez si pornec lista de argumente
   
    while (*format)//Pana cand mai am ce sa citesc din datele de intrare 
    {
    	if(*format == '%'){
    	    //Aceasta este prima categorie pentru printare, caracterele
    		//care lucreaza cu '%', daca intalnesc un astfel de
    		//caracter incrementez formatul si apoi verific ce caracter 
    		//vine dupa el in urmatoarele 6 if-uri  
    		format++;
    		
    		if(*format == 'd'){
    			i = 0;
    			j = 0;
    			memset(c, 0, sizeof 1);
    			//Eliberez vectorul de caractere 
    			intreg = va_arg(ap, int);
    			if(intreg < 0){
    				intreg = intreg*(-1);
    				c[j]='-';
    				j++;
       			}
       			//Daca numarul peste care am dat este negativ il fac pozitiv
       			//si adaug un minus in vectorul de caractere pt a pastra semnul
    			while(intreg){
    				nr = intreg % 10;
					intreg = intreg / 10;
					sir[i] = nr +'0';
					i++;
    			}
    			//Introduc in vectorul sir cifrele din numar in format char
    			//in sens invers 
    			i--;
				while(i>=0){
					c[j] = sir[i];
					i--;
					j++;
				}
				//Ordonez in vectorul c elementele din sir pentru reprezentarea
				//corecta si apoi adaug terminatorul de sir pe ultima pozitie a 
				//vectorului pentru a evita printarea altor caractere dupa
				c[j]= '\0';
				l = strlen(c);
				write_stdout(c, l);
    			counter = counter + l;
    			//Printez ce se afla in vectorul c apoi incrementez counterul de
    			//de caractere printate
      		}
      		
      		if(*format == 'u'){
      			i = 0;
    			j = 0;
    			memset(c, 0, sizeof 1);
    			//Eliberez vectorul de caractere
    			farasemn = va_arg(ap, int);
    			u = (unsigned int)farasemn;
    			//Castez int-ul in unsigned
    			while(u)
				{
					nr = u % 10;
					u = u / 10;
					sir[i] = nr +'0';
					i++;
				}
				//Introduc in vectorul sir cifrele din numar in format char
    			//in sens invers 
				i--;
				while(i>=0){
					c[j] = sir[i];
					i--;
					j++;
				}
				//Ordonez in vectorul c elementele din sir pentru reprezentarea
				//corecta si apoi adaug terminatorul de sir pe ultima pozitie a 
				//vectorului pentru a evita printarea altor caractere dupa
				c[j]='\0';
				l = strlen(c);
				write_stdout(c, l);
				counter = counter + l;
				//Printez ce se afla in vectorul c apoi incrementez counterul de
    			//de caractere printate
      		}
      		
      		if(*format == 'x'){
      			i = 0;
      			j = 0;
      			p = 0;
      			memset(c, 0, sizeof 1);
      			memset(bin, 0, sizeof(bin));
      			memset(hex, 0, sizeof(hex));
      			//Eliberez vectorul de caractere si ceilalti 2 vectori ajutatori
    			hexa = va_arg(ap, int);
    				for (j = 0; j < 32; j++)
					{
						bin[j]=0;
						//Umplu vectorul pentru formatul binar pe 32 de biti cu 0
					}
					j--;
					if(hexa < 0){
						//Verific daca numarul dat este negativ sau pozitiv
						//Daca este negativ il fac pozitiv ca mai apoi sa il 
						//transform in baza 2
						hexa = hexa*(-1);
						while(hexa != 0){
							r = hexa % 2;
							hexa = hexa / 2;
							bin[j] = r;
							j--;
						}
						//Dupa ce la transformat in baza 2 neg numarul obtinut
						for (i = 0; i < 32; i++)
						{
							if(bin[i] == 0)
								bin[i] = 1;
							else 
								bin[i] = 0;
						}
						i = 31;
						//Aduc i-ul pe ultima pozitie a vectorului
						if(bin[i] == 1)
						{//In acest if adaug un bit la finalul numarului negat
							//Si fac modificarile necesare pentru respectare 
							//regulilor de adunare din baza 2
							bin[i] = 0;
							sr = 1;
							k = 1;
							while(sr){
								if(bin[i-k] == 0)
								{
									bin[i-k] = 1;
									sr = 0;
								}
								else
								{
									bin[i-k] = 0;
									//sr = 0;
								}
								k++;
							}
						}
						else{
							bin[i] = 1;
						}
						j = 0;
						for (i = 0; i < 32; i+=4)
						{//In acest for incep procesul de transformare catre baza 16
							//iau cate 4 biti si pentru fiecrae bit inmultesc cu 2 la
							//puterea corespunzatoare 
							//Dupa aceea rezultatul primit il pun in una dintre cele 8 
							//casute din vectorul hex care reprezinta elementul din baza 16
							p = bin[i] * 2 * 2 * 2 + bin[i+1] * 2 * 2 + bin[i+2] * 2 + bin[i+3];
							hex[j] = p;
							j++;
						}
	    
						for (i = 0; i < 8; i++)
						{//In acest for construesc elementul din hexa cu ajutorul vectorului
							//de litere lit si a vectorului hex aflat mai sus
							if(hex[i] > 9){
								c[i] = lit[hex[i]%10];
							}
							else
								c[i] = hex[i] + '0';
						}
						//adaug terminatorul de sir pe ultima pozitie a vectorului 
						//pentru a evita printarea altor caractere dupa
						c[i]='\0';
	    				l = strlen(c);
	    				write_stdout(c, l);
	    				counter = counter + l;
	    				//Printez ce se afla in vectorul c apoi incrementez counterul de
    					//de caractere printate
	    		}
    			else{
    				//Daca numarul nu este negativ
    				i = 0;
    				j = 0;
    				while(hexa){
    					//Impart numarul la 16 si in functie de restul primit adaug in 
    					//vectorul sir caracterele corespunzatoare
    					r = hexa % 16;
    					if(r>9)
							sir[i] = lit[r%10];
						else
							sir[i] = r + '0';
	 			   		i++;
						hexa = hexa / 16;
					}
					i--;
					while(i>=0){
						c[j] = sir[i];
						i--;
						j++;	
    				}
    				//Ordonez in vectorul c elementele din sir pentru reprezentarea
					//corecta si apoi adaug terminatorul de sir pe ultima pozitie a 
					//vectorului pentru a evita printarea altor caractere dupa
    				c[j]='\0';
    				l = strlen(c);
	    			write_stdout(c, l);
	    			counter = counter + l;
	    			//Printez ce se afla in vectorul c apoi incrementez counterul de
    				//de caractere printate
    			}
			}
      		
      		if(*format == 'c'){
      			memset(c, 0, sizeof 1);
      			//Eliberez vectorul de caractere 
    			caracter = (char) va_arg(ap, int);
    			c[0] = caracter;
    			//Pun in vectorul c caracterul primit 
				l = strlen(c);
				write_stdout(c, l);
				counter++;
				//Printez ce se afla in vectorul c apoi incrementez counterul de
    			//de caractere printate
      		}
      		
      		if(*format == 's'){
      			memset(c, 0, sizeof 1);
      			//Eliberez vectorul de caractere 
    			string = va_arg(ap, char *);
    			strcpy(c, string);
    			//Copiez in vectorul c stringul primit
   				l = strlen(c);
				write_stdout(c, l);
    			counter = counter + l;
    			//Printez ce se afla in vectorul c apoi incrementez counterul de
    			//de caractere printate
      		}
      		
      		if(*format == '%'){
      			write_stdout("%", 1);
      			counter++;
      			//Printez caracterul apoi incrementez counterul de
    			//de caractere printate
      		}

      	}
      	else{
      		if(*format == '\\'){
      			//Aceasta e a doua categorie pentru printare, care se bazeaza 
      			//pe caracterul '\' si afisez in functie de cerinte '\', n, t,
      			//Tot in aceasta categoie am inclus si spatiul
      			write_stdout("\\", 1);
      	        counter++;
      	        //Printez caracterul apoi incrementez counterul de
    			//de caractere printate

      			if(*format == '\n'){
      				write_stdout("\n", 1);
      				counter++;
      			//Printez caracterul apoi incrementez counterul de
    			//de caractere printate
      			}
      	
      			if(*format == '\t'){
      				write_stdout("\t", 1);
      				counter++;
      			//Printez caracterul apoi incrementez counterul de
    			//de caractere printate
      			}
      	
      			if(*format == ' '){
      				write_stdout(" ", 1);
      				counter++;
      			//Printez caracterul apoi incrementez counterul de
    			//de caractere printate
        		}
        	}
        	else{
        		//Deoarece am consumat cerintele care cer printarea intr-o anumita 
        		//modalitate inputul primit de la format este printat asa cum este 
        		//primit
        		l = sizeof(*format);
        		write_stdout(format, l);
        		counter++;
        		//Printez caracterul apoi incrementez counterul de
    			//de caractere printate
        	}
        	
        }
    	format++;
    	//Incrementez formatul pentru a ajunge la urmatoarele cerinte de input
    }
    free(c);
    //Eliberez vectorul alocat dinamic
    va_end(ap);
    //Inchid lista de argumente

	return counter;
}
