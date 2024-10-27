#define MAX_MESSAGES_PER_PAGE 250

#include <time.h>
#include "specific.c"

int query_size;

void Send(char *ch)
{
printf("Content-Type: text/html\n\n\
<!DOCTYPE html>\n\
<html>\n\
<head>\n\
<title>Xpress0</title>\n\
<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n\
<meta charset=\"utf-8\">\n\
<link rel=\"stylesheet\" href=\"/xpresso/themes/press.min.css\" />\n\
<link rel=\"stylesheet\" href=\"/xpresso/themes/jquery.mobile.icons.min.css\" />\n\
<link rel=\"stylesheet\" href=\"/jq/jquery.mobile.structure-1.4.5.min.css\" />\n\
<script src=\"/jq/demos/js/jquery.min.js\"></script>\n\
<script src=\"/jq/jquery.mobile-1.4.5.min.js\"></script>\n\
</head>\n\
<body>\n\
%s<br>\n\
</body>\n\
</html>\n",ch);
exit(0);
}

int get_weekday(char * str) {
  struct tm tm;
  memset((void *) &tm, 0, sizeof(tm));
  if (strptime(str, "%Y-%m-%d", &tm) != NULL) {
    time_t t = mktime(&tm);
    if (t >= 0) {
      return localtime(&t)->tm_wday; // Sunday=0, Monday=1, etc.
    }
  }
  return -1;
}

void alerte(char *ch)
{
printf("%s\n",ch);
}

void elimine_blancs(char *chaine)
{
int i,start;
char *res;

res=(char *)malloc(strlen(chaine)+1);
i=start=0;
do
	{
	res[start]=chaine[i];
	if(res[start]!=' ') start++;
	i++;
	}
while(i<=strlen(chaine));
strcpy(chaine,res);
free(res);
}

void prepare_contenu(char *chaine)
{
int i,start;
char *res;

res=(char *)malloc(strlen(chaine)*2);
i=start=0;
do
	{
	if(chaine[i]=='\'')
		{
		res[start]='\\';
		start++;
		}
	res[start]=chaine[i];
	start++;
	i++;
	}
while(i<=strlen(chaine));
strcpy(chaine,res);
free(res);
}

void magiczero(int num, char *chaine)
{
if(num<10) sprintf(chaine,"0%d",num);
else sprintf(chaine,"%d",num);
}

void url_decode(char *chaine)
{
int i,start;
char *res;

res=(char *)malloc(strlen(chaine)+1);
i=start=0;
do
	{
	res[start]=chaine[i];
	if(chaine[i]=='%' && chaine[i+1]=='C' && chaine[i+2]=='3' && chaine[i+3]=='%' && chaine[i+4]=='A' && chaine[i+5]=='9')
		{
		res[start]=0xC3;
		res[start+1]=0xA9;
		start++;
		i+=5;
		}
	if(chaine[i]=='%' && chaine[i+1]=='C' && chaine[i+2]=='3' && chaine[i+3]=='%' && chaine[i+4]=='A' && chaine[i+5]=='8')
		{
		res[start]=0xC3;
		res[start+1]=0xA8;
		start++;
		i+=5;
		}
	if(chaine[i]=='%' && chaine[i+1]=='C' && chaine[i+2]=='3' && chaine[i+3]=='%' && chaine[i+4]=='8' && chaine[i+5]=='2')
		{
		res[start]=0xC3;
		res[start+1]=0x82;
		start++;
		i+=5;
		}
	if(chaine[i]=='%' && chaine[i+1]=='C' && chaine[i+2]=='3' && chaine[i+3]=='%' && chaine[i+4]=='8' && chaine[i+5]=='4')
		{
		res[start]=0xC3;
		res[start+1]=0x84;
		start++;
		i+=5;
		}
	if(chaine[i]=='%' && chaine[i+1]=='C' && chaine[i+2]=='3' && chaine[i+3]=='%' && chaine[i+4]=='8' && chaine[i+5]=='0')
		{
		res[start]=0xC3;
		res[start+1]=0x80;
		start++;
		i+=5;
		}
	if(chaine[i]=='%' && chaine[i+1]=='C' && chaine[i+2]=='3' && chaine[i+3]=='%' && chaine[i+4]=='8' && chaine[i+5]=='6')
		{
		res[start]=0xC3;
		res[start+1]=0x86;
		start++;
		i+=5;
		}
	if(chaine[i]=='%' && chaine[i+1]=='C' && chaine[i+2]=='3' && chaine[i+3]=='%' && chaine[i+4]=='8' && chaine[i+5]=='8')
		{
		res[start]=0xC3;
		res[start+1]=0x88;
		start++;
		i+=5;
		}
	if(chaine[i]=='%' && chaine[i+1]=='C' && chaine[i+2]=='3' && chaine[i+3]=='%' && chaine[i+4]=='8' && chaine[i+5]=='A')
		{
		res[start]=0xC3;
		res[start+1]=0x8A;
		start++;
		i+=5;
		}
	if(chaine[i]=='%' && chaine[i+1]=='C' && chaine[i+2]=='3' && chaine[i+3]=='%' && chaine[i+4]=='8' && chaine[i+5]=='B')
		{
		res[start]=0xC3;
		res[start+1]=0x8B;
		start++;
		i+=5;
		}
	if(chaine[i]=='%' && chaine[i+1]=='C' && chaine[i+2]=='3' && chaine[i+3]=='%' && chaine[i+4]=='8' && chaine[i+5]=='9')
		{
		res[start]=0xC3;
		res[start+1]=0x89;
		start++;
		i+=5;
		}
	if(chaine[i]=='%' && chaine[i+1]=='C' && chaine[i+2]=='3' && chaine[i+3]=='%' && chaine[i+4]=='8' && chaine[i+5]=='E')
		{
		res[start]=0xC3;
		res[start+1]=0x8E;
		start++;
		i+=5;
		}
	if(chaine[i]=='%' && chaine[i+1]=='C' && chaine[i+2]=='3' && chaine[i+3]=='%' && chaine[i+4]=='8' && chaine[i+5]=='F')
		{
		res[start]=0xC3;
		res[start+1]=0x8F;
		start++;
		i+=5;
		}
	if(chaine[i]=='%' && chaine[i+1]=='C' && chaine[i+2]=='3' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='4')
		{
		res[start]=0xC3;
		res[start+1]=0x94;
		start++;
		i+=5;
		}
	if(chaine[i]=='%' && chaine[i+1]=='C' && chaine[i+2]=='3' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='9')
		{
		res[start]=0xC3;
		res[start+1]=0x99;
		start++;
		i+=5;
		}
	if(chaine[i]=='%' && chaine[i+1]=='C' && chaine[i+2]=='3' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='C')
		{
		res[start]=0xC3;
		res[start+1]=0x9C;
		start++;
		i+=5;
		}
	if(chaine[i]=='%' && chaine[i+1]=='C' && chaine[i+2]=='3' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='B')
		{
		res[start]=0xC3;
		res[start+1]=0x9B;
		start++;
		i+=5;
		}
	if(chaine[i]=='%' && chaine[i+1]=='C' && chaine[i+2]=='5' && chaine[i+3]=='%' && chaine[i+4]=='B' && chaine[i+5]=='8')
		{
		res[start]=0xC5;
		res[start+1]=0xB8;
		start++;
		i+=5;
		}
	if(chaine[i]=='%' && chaine[i+1]=='C' && chaine[i+2]=='3' && chaine[i+3]=='%' && chaine[i+4]=='A' && chaine[i+5]=='A')
		{
		res[start]=0xC3;
		res[start+1]=0xAA;
		start++;
		i+=5;
		}
	if(chaine[i]=='%' && chaine[i+1]=='C' && chaine[i+2]=='3' && chaine[i+3]=='%' && chaine[i+4]=='A' && chaine[i+5]=='B')
		{
		res[start]=0xC3;
		res[start+1]=0xAB;
		start++;
		i+=5;
		}
	if(chaine[i]=='%' && chaine[i+1]=='C' && chaine[i+2]=='3' && chaine[i+3]=='%' && chaine[i+4]=='A' && chaine[i+5]=='2')
		{
		res[start]=0xC3;
		res[start+1]=0xA2;
		start++;
		i+=5;
		}
	if(chaine[i]=='%' && chaine[i+1]=='C' && chaine[i+2]=='3' && chaine[i+3]=='%' && chaine[i+4]=='A' && chaine[i+5]=='0')
		{
		res[start]=0xC3;
		res[start+1]=0xA0;
		start++;
		i+=5;
		}
	if(chaine[i]=='%' && chaine[i+1]=='C' && chaine[i+2]=='3' && chaine[i+3]=='%' && chaine[i+4]=='A' && chaine[i+5]=='6')
		{
		res[start]=0xC3;
		res[start+1]=0xA6;
		start++;
		i+=5;
		}
	if(chaine[i]=='%' && chaine[i+1]=='C' && chaine[i+2]=='2' && chaine[i+3]=='%' && chaine[i+4]=='A' && chaine[i+5]=='B')
		{
		res[start]=0xC2;
		res[start+1]=0xAB;
		start++;
		i+=5;
		}
	if(chaine[i]=='%' && chaine[i+1]=='C' && chaine[i+2]=='2' && chaine[i+3]=='%' && chaine[i+4]=='B' && chaine[i+5]=='B')
		{
		res[start]=0xC2;
		res[start+1]=0xBB;
		start++;
		i+=5;
		}
	if(chaine[i]=='%' && chaine[i+1]=='C' && chaine[i+2]=='3' && chaine[i+3]=='%' && chaine[i+4]=='A' && chaine[i+5]=='E')
		{
		res[start]=0xC3;
		res[start+1]=0xAE;
		start++;
		i+=5;
		}
	if(chaine[i]=='%' && chaine[i+1]=='C' && chaine[i+2]=='3' && chaine[i+3]=='%' && chaine[i+4]=='A' && chaine[i+5]=='F')
		{
		res[start]=0xC3;
		res[start+1]=0xAF;
		start++;
		i+=5;
		}
	if(chaine[i]=='%' && chaine[i+1]=='C' && chaine[i+2]=='3' && chaine[i+3]=='%' && chaine[i+4]=='B' && chaine[i+5]=='4')
		{
		res[start]=0xC3;
		res[start+1]=0xB4;
		start++;
		i+=5;
		}
	if(chaine[i]=='%' && chaine[i+1]=='C' && chaine[i+2]=='3' && chaine[i+3]=='%' && chaine[i+4]=='A' && chaine[i+5]=='4')
		{
		res[start]=0xC3;
		res[start+1]=0xA4;
		start++;
		i+=5;
		}
	if(chaine[i]=='%' && chaine[i+1]=='C' && chaine[i+2]=='3' && chaine[i+3]=='%' && chaine[i+4]=='B' && chaine[i+5]=='6')
		{
		res[start]=0xC3;
		res[start+1]=0xB6;
		start++;
		i+=5;
		}
	if(chaine[i]=='%' && chaine[i+1]=='C' && chaine[i+2]=='5' && chaine[i+3]=='%' && chaine[i+4]=='B' && chaine[i+5]=='7')
		{
		res[start]=0xC5;
		res[start+1]=0xB7;
		start++;
		i+=5;
		}
	if(chaine[i]=='%' && chaine[i+1]=='C' && chaine[i+2]=='5' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='3')
		{
		res[start]=0xC5;
		res[start+1]=0x93;
		start++;
		i+=5;
		}
	if(chaine[i]=='%' && chaine[i+1]=='C' && chaine[i+2]=='3' && chaine[i+3]=='%' && chaine[i+4]=='B' && chaine[i+5]=='9')
		{
		res[start]=0xC3;
		res[start+1]=0xB9;
		start++;
		i+=5;
		}
	if(chaine[i]=='%' && chaine[i+1]=='C' && chaine[i+2]=='3' && chaine[i+3]=='%' && chaine[i+4]=='B' && chaine[i+5]=='C')
		{
		res[start]=0xC3;
		res[start+1]=0xBC;
		start++;
		i+=5;
		}
	if(chaine[i]=='%' && chaine[i+1]=='C' && chaine[i+2]=='3' && chaine[i+3]=='%' && chaine[i+4]=='B' && chaine[i+5]=='B')
		{
		res[start]=0xC3;
		res[start+1]=0xBB;
		start++;
		i+=5;
		}
	if(chaine[i]=='%' && chaine[i+1]=='C' && chaine[i+2]=='3' && chaine[i+3]=='%' && chaine[i+4]=='B' && chaine[i+5]=='F')
		{
		res[start]=0xC3;
		res[start+1]=0xBF;
		start++;
		i+=5;
		}
	if(chaine[i]=='%' && chaine[i+1]=='C' && chaine[i+2]=='2' && chaine[i+3]=='%' && chaine[i+4]=='B' && chaine[i+5]=='0')
		{
		res[start]=0xC2;
		res[start+1]=0xB0;
		start++;
		i+=5;
		}
	if(chaine[i]=='%' && chaine[i+1]=='C' && chaine[i+2]=='2' && chaine[i+3]=='%' && chaine[i+4]=='A' && chaine[i+5]=='7')
		{
		res[start]=0xC2;
		res[start+1]=0xA7;
		start++;
		i+=5;
		}
	if(chaine[i]=='%' && chaine[i+1]=='C' && chaine[i+2]=='2' && chaine[i+3]=='%' && chaine[i+4]=='B' && chaine[i+5]=='5')
		{
		res[start]=0xC2;
		res[start+1]=0xB5;
		start++;
		i+=5;
		}
	if(chaine[i]=='%' && chaine[i+1]=='C' && chaine[i+2]=='2' && chaine[i+3]=='%' && chaine[i+4]=='A' && chaine[i+5]=='3')
		{
		res[start]=0xC2;
		res[start+1]=0xA3;
		start++;
		i+=5;
		}
	if(chaine[i]=='%' && chaine[i+1]=='C' && chaine[i+2]=='3' && chaine[i+3]=='%' && chaine[i+4]=='A' && chaine[i+5]=='7')
		{
		res[start]=0xC3;
		res[start+1]=0xA7;
		start++;
		i+=5;
		}
	if(chaine[i]=='%' && chaine[i+1]=='C' && chaine[i+2]=='5' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='2')
		{
		res[start]=0xC5;
		res[start+1]=0x92;
		start++;
		i+=5;
		}
	if(chaine[i]=='%' && chaine[i+1]=='0' && chaine[i+2]=='D' && chaine[i+3]=='%' && chaine[i+4]=='0' && chaine[i+5]=='A')
		{
		res[start]='<';
		res[start+1]='b';
		res[start+2]='r';
		res[start+3]='>';
		start+=3;
		i+=5;
		}
	if(chaine[i]=='%' && chaine[i+1]=='2' && chaine[i+2]=='3')
		{
		res[start]='#';
		i+=2;
		}
	if(chaine[i]=='%' && chaine[i+1]=='7' && chaine[i+2]=='B')
		{
		res[start]='{';
		i+=2;
		}
	if(chaine[i]=='%' && chaine[i+1]=='5' && chaine[i+2]=='B')
		{
		res[start]='[';
		i+=2;
		}
	if(chaine[i]=='%' && chaine[i+1]=='7' && chaine[i+2]=='C')
		{
		res[start]='|';
		i+=2;
		}
	if(chaine[i]=='%' && chaine[i+1]=='6' && chaine[i+2]=='0')
		{
		res[start]='`';
		i+=2;
		}
	if(chaine[i]=='%' && chaine[i+1]=='5' && chaine[i+2]=='C')
		{
		res[start]=' ';
		i+=2;
		}
	if(chaine[i]=='%' && chaine[i+1]=='5' && chaine[i+2]=='E')
		{
		res[start]='^';
		i+=2;
		}
	if(chaine[i]=='%' && chaine[i+1]=='5' && chaine[i+2]=='D')
		{
		res[start]=']';
		i+=2;
		}
	if(chaine[i]=='%' && chaine[i+1]=='7' && chaine[i+2]=='D')
		{
		res[start]='}';
		i+=2;
		}
	if(chaine[i]=='%' && chaine[i+1]=='2' && chaine[i+2]=='C')
		{
		res[start]=',';
		i+=2;
		}
	if(chaine[i]=='%' && chaine[i+1]=='2' && chaine[i+2]=='4')
		{
		res[start]='$';
		i+=2;
		}
	if(chaine[i]=='%' && chaine[i+1]=='3' && chaine[i+2]=='B')
		{
		res[start]=';';
		i+=2;
		}
	if(chaine[i]=='%' && chaine[i+1]=='2' && chaine[i+2]=='5')
		{
		res[start]='%';
		i+=2;
		}
	if(chaine[i]=='%' && chaine[i+1]=='3' && chaine[i+2]=='A')
		{
		res[start]=':';
		i+=2;
		}
	if(chaine[i]=='%' && chaine[i+1]=='2' && chaine[i+2]=='F')
		{
		res[start]='/';
		i+=2;
		}
	if(chaine[i]=='%' && chaine[i+1]=='3' && chaine[i+2]=='C')
		{
		res[start]='<';
		i+=2;
		}
	if(chaine[i]=='%' && chaine[i+1]=='3' && chaine[i+2]=='E')
		{
		res[start]='>';
		i+=2;
		}
	if(chaine[i]=='%' && chaine[i+1]=='2' && chaine[i+2]=='2')
		{
		res[start]='"';
		i+=2;
		}
	if(chaine[i]=='%' && chaine[i+1]=='E' && chaine[i+2]=='2' && chaine[i+3]=='%' && chaine[i+4]=='8' && chaine[i+5]=='2' && chaine[i+6]=='%' && chaine[i+7]=='A' && chaine[i+8]=='C')
		{
		res[start]=0xE2;
		res[start+1]=0x82;
		res[start+2]=0xAC;
		start += 2;
		i+=8;
		}
	if(chaine[i]=='%' && chaine[i+1]=='E' && chaine[i+2]=='2' && chaine[i+3]=='%' && chaine[i+4]=='8' && chaine[i+5]=='0' && chaine[i+6]=='%' && chaine[i+7]=='9' && chaine[i+8]=='9')
		{
		res[start]=0xE2;
		res[start+1]=0x80;
		res[start+2]=0x99;
		start += 2;
		i+=8;
		}
	if(chaine[i]=='%' && chaine[i+1]=='E' && chaine[i+2]=='2' && chaine[i+3]=='%' && chaine[i+4]=='8' && chaine[i+5]=='0' && chaine[i+6]=='%' && chaine[i+7]=='A' && chaine[i+8]=='6')
		{
		res[start]=0xE2;
		res[start+1]=0x80;
		res[start+2]=0xA6;
		start += 2;
		i+=8;
		}
	if(chaine[i]=='%' && chaine[i+1]=='E' && chaine[i+2]=='2' && chaine[i+3]=='%' && chaine[i+4]=='8' && chaine[i+5]=='0' && chaine[i+6]=='%' && chaine[i+7]=='A' && chaine[i+8]=='F')
		{
		res[start]=0xE2;
		res[start+1]=0x80;
		res[start+2]=0xAF;
		start += 2;
		i+=8;
		}
	if(chaine[i]=='%' && chaine[i+1]=='E' && chaine[i+2]=='2' && chaine[i+3]=='%' && chaine[i+4]=='8' && chaine[i+5]=='0' && chaine[i+6]=='%' && chaine[i+7]=='9' && chaine[i+8]=='3')
		{
		res[start]=0xE2;
		res[start+1]=0x80;
		res[start+2]=0x93;
		start += 2;
		i+=8;
		}
	if(chaine[i]=='%' && chaine[i+1]=='2' && chaine[i+2]=='6')
		{
		res[start]='&';
		i+=2;
		}
	if(chaine[i]=='%' && chaine[i+1]=='4' && chaine[i+2]=='0')
		{
		res[start]='@';
		i+=2;
		}
	if(chaine[i]=='%' && chaine[i+1]=='3' && chaine[i+2]=='D')
		{
		res[start]='=';
		i+=2;
		}
	if(chaine[i]=='%' && chaine[i+1]=='2' && chaine[i+2]=='B')
		{
		res[start]='+';
		i+=2;
		}
	if(chaine[i]=='%' && chaine[i+1]=='3' && chaine[i+2]=='F')
		{
		res[start]='?';
		i+=2;
		}
	// support des emojis
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='7' && chaine[i+9]=='%' && chaine[i+10]=='A' && chaine[i+11]=='B' && chaine[i+12]=='%' && chaine[i+13]=='F' && chaine[i+14]=='0' && chaine[i+15]=='%' && chaine[i+16]=='9' && chaine[i+17]=='F' && chaine[i+18]=='%' && chaine[i+19]=='8' && chaine[i+20]=='7' && chaine[i+21]=='%' && chaine[i+22]=='B' && chaine[i+23]=='7' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x87;
		res[start+3]=0xAB;
		res[start+4]=0xF0;
		res[start+5]=0x9F;
		res[start+6]=0x87;
		res[start+7]=0xB7;
		start+=7;
		i+=23;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='9' && chaine[i+8]=='8' && chaine[i+9]=='%' && chaine[i+10]=='8' && chaine[i+11]=='0' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x98;
		res[start+3]=0x80;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='9' && chaine[i+8]=='8' && chaine[i+9]=='%' && chaine[i+10]=='8' && chaine[i+11]=='3' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x98;
		res[start+3]=0x83;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='9' && chaine[i+8]=='8' && chaine[i+9]=='%' && chaine[i+10]=='8' && chaine[i+11]=='4' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x98;
		res[start+3]=0x84;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='9' && chaine[i+8]=='8' && chaine[i+9]=='%' && chaine[i+10]=='8' && chaine[i+11]=='1' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x98;
		res[start+3]=0x81;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='9' && chaine[i+8]=='8' && chaine[i+9]=='%' && chaine[i+10]=='8' && chaine[i+11]=='6' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x98;
		res[start+3]=0x86;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='9' && chaine[i+8]=='8' && chaine[i+9]=='%' && chaine[i+10]=='8' && chaine[i+11]=='5' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x98;
		res[start+3]=0x85;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='A' && chaine[i+8]=='4' && chaine[i+9]=='%' && chaine[i+10]=='A' && chaine[i+11]=='3' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0xA4;
		res[start+3]=0xA3;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='9' && chaine[i+8]=='8' && chaine[i+9]=='%' && chaine[i+10]=='8' && chaine[i+11]=='2' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x98;
		res[start+3]=0x82;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='9' && chaine[i+8]=='9' && chaine[i+9]=='%' && chaine[i+10]=='8' && chaine[i+11]=='2' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x99;
		res[start+3]=0x82;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='9' && chaine[i+8]=='9' && chaine[i+9]=='%' && chaine[i+10]=='8' && chaine[i+11]=='3' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x99;
		res[start+3]=0x83;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='9' && chaine[i+8]=='8' && chaine[i+9]=='%' && chaine[i+10]=='8' && chaine[i+11]=='9' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x98;
		res[start+3]=0x89;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='9' && chaine[i+8]=='8' && chaine[i+9]=='%' && chaine[i+10]=='8' && chaine[i+11]=='A' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x98;
		res[start+3]=0x8A;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='9' && chaine[i+8]=='8' && chaine[i+9]=='%' && chaine[i+10]=='8' && chaine[i+11]=='7' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x98;
		res[start+3]=0x87;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='A' && chaine[i+8]=='5' && chaine[i+9]=='%' && chaine[i+10]=='B' && chaine[i+11]=='0' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0xA5;
		res[start+3]=0xB0;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='9' && chaine[i+8]=='8' && chaine[i+9]=='%' && chaine[i+10]=='8' && chaine[i+11]=='D' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x98;
		res[start+3]=0x8D;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='A' && chaine[i+8]=='4' && chaine[i+9]=='%' && chaine[i+10]=='A' && chaine[i+11]=='9' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0xA4;
		res[start+3]=0xA9;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='9' && chaine[i+8]=='8' && chaine[i+9]=='%' && chaine[i+10]=='9' && chaine[i+11]=='8' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x98;
		res[start+3]=0x98;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='9' && chaine[i+8]=='8' && chaine[i+9]=='%' && chaine[i+10]=='9' && chaine[i+11]=='7' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x98;
		res[start+3]=0x97;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='9' && chaine[i+8]=='8' && chaine[i+9]=='%' && chaine[i+10]=='8' && chaine[i+11]=='B' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x98;
		res[start+3]=0x8B;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='9' && chaine[i+8]=='8' && chaine[i+9]=='%' && chaine[i+10]=='9' && chaine[i+11]=='B' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x98;
		res[start+3]=0x9B;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='A' && chaine[i+8]=='4' && chaine[i+9]=='%' && chaine[i+10]=='A' && chaine[i+11]=='A' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0xA4;
		res[start+3]=0xAA;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='9' && chaine[i+8]=='8' && chaine[i+9]=='%' && chaine[i+10]=='9' && chaine[i+11]=='D' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x98;
		res[start+3]=0x9D;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='A' && chaine[i+8]=='4' && chaine[i+9]=='%' && chaine[i+10]=='9' && chaine[i+11]=='7' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0xA4;
		res[start+3]=0x97;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='A' && chaine[i+8]=='4' && chaine[i+9]=='%' && chaine[i+10]=='A' && chaine[i+11]=='D' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0xA4;
		res[start+3]=0xAD;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='A' && chaine[i+8]=='4' && chaine[i+9]=='%' && chaine[i+10]=='A' && chaine[i+11]=='B' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0xA4;
		res[start+3]=0xAB;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='A' && chaine[i+8]=='4' && chaine[i+9]=='%' && chaine[i+10]=='9' && chaine[i+11]=='4' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0xA4;
		res[start+3]=0x94;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='A' && chaine[i+8]=='4' && chaine[i+9]=='%' && chaine[i+10]=='9' && chaine[i+11]=='0' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0xA4;
		res[start+3]=0x90;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='A' && chaine[i+8]=='4' && chaine[i+9]=='%' && chaine[i+10]=='A' && chaine[i+11]=='8' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0xA4;
		res[start+3]=0xA8;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='9' && chaine[i+8]=='8' && chaine[i+9]=='%' && chaine[i+10]=='8' && chaine[i+11]=='F' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x98;
		res[start+3]=0x8F;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='9' && chaine[i+8]=='8' && chaine[i+9]=='%' && chaine[i+10]=='9' && chaine[i+11]=='2' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x98;
		res[start+3]=0x92;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='9' && chaine[i+8]=='9' && chaine[i+9]=='%' && chaine[i+10]=='8' && chaine[i+11]=='4' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x99;
		res[start+3]=0x84;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='9' && chaine[i+8]=='8' && chaine[i+9]=='%' && chaine[i+10]=='A' && chaine[i+11]=='C' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x98;
		res[start+3]=0xAC;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='9' && chaine[i+8]=='8' && chaine[i+9]=='%' && chaine[i+10]=='9' && chaine[i+11]=='4' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x98;
		res[start+3]=0x94;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='9' && chaine[i+8]=='8' && chaine[i+9]=='%' && chaine[i+10]=='B' && chaine[i+11]=='4' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x98;
		res[start+3]=0xB4;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='9' && chaine[i+8]=='8' && chaine[i+9]=='%' && chaine[i+10]=='B' && chaine[i+11]=='7' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x98;
		res[start+3]=0xB7;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='A' && chaine[i+8]=='4' && chaine[i+9]=='%' && chaine[i+10]=='9' && chaine[i+11]=='2' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0xA4;
		res[start+3]=0x92;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='A' && chaine[i+8]=='4' && chaine[i+9]=='%' && chaine[i+10]=='9' && chaine[i+11]=='5' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0xA4;
		res[start+3]=0x95;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='A' && chaine[i+8]=='4' && chaine[i+9]=='%' && chaine[i+10]=='A' && chaine[i+11]=='2' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0xA4;
		res[start+3]=0xA2;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='A' && chaine[i+8]=='4' && chaine[i+9]=='%' && chaine[i+10]=='A' && chaine[i+11]=='E' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0xA4;
		res[start+3]=0xAE;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='A' && chaine[i+8]=='5' && chaine[i+9]=='%' && chaine[i+10]=='B' && chaine[i+11]=='5' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0xA5;
		res[start+3]=0xB5;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='A' && chaine[i+8]=='5' && chaine[i+9]=='%' && chaine[i+10]=='B' && chaine[i+11]=='6' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0xA5;
		res[start+3]=0xB6;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='A' && chaine[i+8]=='5' && chaine[i+9]=='%' && chaine[i+10]=='B' && chaine[i+11]=='4' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0xA5;
		res[start+3]=0xB4;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='9' && chaine[i+8]=='8' && chaine[i+9]=='%' && chaine[i+10]=='8' && chaine[i+11]=='E' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x98;
		res[start+3]=0x8E;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='A' && chaine[i+8]=='4' && chaine[i+9]=='%' && chaine[i+10]=='9' && chaine[i+11]=='3' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0xA4;
		res[start+3]=0x93;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='A' && chaine[i+8]=='7' && chaine[i+9]=='%' && chaine[i+10]=='9' && chaine[i+11]=='0' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0xA7;
		res[start+3]=0x90;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='9' && chaine[i+8]=='8' && chaine[i+9]=='%' && chaine[i+10]=='9' && chaine[i+11]=='5' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x98;
		res[start+3]=0x95;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='9' && chaine[i+8]=='8' && chaine[i+9]=='%' && chaine[i+10]=='9' && chaine[i+11]=='F' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x98;
		res[start+3]=0x9F;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='E' && chaine[i+2]=='2' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='8' && chaine[i+6]=='%' && chaine[i+7]=='B' && chaine[i+8]=='9' && chaine[i+9]=='%' && chaine[i+10]=='E' && chaine[i+11]=='F' && chaine[i+12]=='%' && chaine[i+13]=='B' && chaine[i+14]=='8' && chaine[i+15]=='%' && chaine[i+16]=='8' && chaine[i+17]=='F' )
		{
		res[start]=0xE2;
		res[start+1]=0x98;
		res[start+2]=0xB9;
		res[start+3]=0xEF;
		res[start+4]=0xB8;
		res[start+5]=0x8F;
		start+=5;
		i+=17;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='9' && chaine[i+8]=='8' && chaine[i+9]=='%' && chaine[i+10]=='A' && chaine[i+11]=='E' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x98;
		res[start+3]=0xAE;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='9' && chaine[i+8]=='8' && chaine[i+9]=='%' && chaine[i+10]=='B' && chaine[i+11]=='2' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x98;
		res[start+3]=0xB2;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='9' && chaine[i+8]=='8' && chaine[i+9]=='%' && chaine[i+10]=='A' && chaine[i+11]=='5' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x98;
		res[start+3]=0xA5;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='9' && chaine[i+8]=='8' && chaine[i+9]=='%' && chaine[i+10]=='A' && chaine[i+11]=='2' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x98;
		res[start+3]=0xA2;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='9' && chaine[i+8]=='8' && chaine[i+9]=='%' && chaine[i+10]=='A' && chaine[i+11]=='D' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x98;
		res[start+3]=0xAD;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='9' && chaine[i+8]=='8' && chaine[i+9]=='%' && chaine[i+10]=='A' && chaine[i+11]=='4' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x98;
		res[start+3]=0xA4;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='A' && chaine[i+8]=='5' && chaine[i+9]=='%' && chaine[i+10]=='B' && chaine[i+11]=='3' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0xA5;
		res[start+3]=0xB3;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='9' && chaine[i+8]=='8' && chaine[i+9]=='%' && chaine[i+10]=='A' && chaine[i+11]=='1' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x98;
		res[start+3]=0xA1;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='9' && chaine[i+8]=='2' && chaine[i+9]=='%' && chaine[i+10]=='8' && chaine[i+11]=='0' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x92;
		res[start+3]=0x80;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='E' && chaine[i+2]=='2' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='8' && chaine[i+6]=='%' && chaine[i+7]=='A' && chaine[i+8]=='0' && chaine[i+9]=='%' && chaine[i+10]=='E' && chaine[i+11]=='F' && chaine[i+12]=='%' && chaine[i+13]=='B' && chaine[i+14]=='8' && chaine[i+15]=='%' && chaine[i+16]=='8' && chaine[i+17]=='F' )
		{
		res[start]=0xE2;
		res[start+1]=0x98;
		res[start+2]=0xA0;
		res[start+3]=0xEF;
		res[start+4]=0xB8;
		res[start+5]=0x8F;
		start+=5;
		i+=17;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='9' && chaine[i+8]=='2' && chaine[i+9]=='%' && chaine[i+10]=='A' && chaine[i+11]=='9' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x92;
		res[start+3]=0xA9;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='A' && chaine[i+8]=='4' && chaine[i+9]=='%' && chaine[i+10]=='A' && chaine[i+11]=='1' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0xA4;
		res[start+3]=0xA1;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='9' && chaine[i+8]=='1' && chaine[i+9]=='%' && chaine[i+10]=='B' && chaine[i+11]=='B' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x91;
		res[start+3]=0xBB;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='9' && chaine[i+8]=='1' && chaine[i+9]=='%' && chaine[i+10]=='B' && chaine[i+11]=='D' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x91;
		res[start+3]=0xBD;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='A' && chaine[i+8]=='4' && chaine[i+9]=='%' && chaine[i+10]=='9' && chaine[i+11]=='6' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0xA4;
		res[start+3]=0x96;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='9' && chaine[i+8]=='2' && chaine[i+9]=='%' && chaine[i+10]=='8' && chaine[i+11]=='B' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x92;
		res[start+3]=0x8B;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='9' && chaine[i+8]=='6' && chaine[i+9]=='%' && chaine[i+10]=='9' && chaine[i+11]=='0' && chaine[i+12]=='%' && chaine[i+13]=='E' && chaine[i+14]=='F' && chaine[i+15]=='%' && chaine[i+16]=='B' && chaine[i+17]=='8' && chaine[i+18]=='%' && chaine[i+19]=='8' && chaine[i+20]=='F' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x96;
		res[start+3]=0x90;
		res[start+4]=0xEF;
		res[start+5]=0xB8;
		res[start+6]=0x8F;
		start+=6;
		i+=20;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='9' && chaine[i+8]=='6' && chaine[i+9]=='%' && chaine[i+10]=='9' && chaine[i+11]=='6' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x96;
		res[start+3]=0x96;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='9' && chaine[i+8]=='1' && chaine[i+9]=='%' && chaine[i+10]=='8' && chaine[i+11]=='C' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x91;
		res[start+3]=0x8C;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='E' && chaine[i+2]=='2' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='C' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='C' && chaine[i+9]=='%' && chaine[i+10]=='E' && chaine[i+11]=='F' && chaine[i+12]=='%' && chaine[i+13]=='B' && chaine[i+14]=='8' && chaine[i+15]=='%' && chaine[i+16]=='8' && chaine[i+17]=='F' )
		{
		res[start]=0xE2;
		res[start+1]=0x9C;
		res[start+2]=0x8C;
		res[start+3]=0xEF;
		res[start+4]=0xB8;
		res[start+5]=0x8F;
		start+=5;
		i+=17;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='A' && chaine[i+8]=='4' && chaine[i+9]=='%' && chaine[i+10]=='9' && chaine[i+11]=='E' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0xA4;
		res[start+3]=0x9E;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='9' && chaine[i+8]=='6' && chaine[i+9]=='%' && chaine[i+10]=='9' && chaine[i+11]=='5' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x96;
		res[start+3]=0x95;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='9' && chaine[i+8]=='1' && chaine[i+9]=='%' && chaine[i+10]=='8' && chaine[i+11]=='D' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x91;
		res[start+3]=0x8D;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='9' && chaine[i+8]=='1' && chaine[i+9]=='%' && chaine[i+10]=='8' && chaine[i+11]=='E' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x91;
		res[start+3]=0x8E;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='9' && chaine[i+8]=='1' && chaine[i+9]=='%' && chaine[i+10]=='8' && chaine[i+11]=='A' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x91;
		res[start+3]=0x8A;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='A' && chaine[i+8]=='4' && chaine[i+9]=='%' && chaine[i+10]=='9' && chaine[i+11]=='D' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0xA4;
		res[start+3]=0x9D;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='9' && chaine[i+8]=='9' && chaine[i+9]=='%' && chaine[i+10]=='8' && chaine[i+11]=='F' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x99;
		res[start+3]=0x8F;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='9' && chaine[i+8]=='2' && chaine[i+9]=='%' && chaine[i+10]=='A' && chaine[i+11]=='A' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x92;
		res[start+3]=0xAA;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='9' && chaine[i+8]=='1' && chaine[i+9]=='%' && chaine[i+10]=='8' && chaine[i+11]=='0' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x91;
		res[start+3]=0x80;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='E' && chaine[i+9]=='%' && chaine[i+10]=='8' && chaine[i+11]=='5' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x8E;
		res[start+3]=0x85;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='E' && chaine[i+2]=='2' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='8' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='2' && chaine[i+9]=='%' && chaine[i+10]=='E' && chaine[i+11]=='F' && chaine[i+12]=='%' && chaine[i+13]=='B' && chaine[i+14]=='8' && chaine[i+15]=='%' && chaine[i+16]=='8' && chaine[i+17]=='F' )
		{
		res[start]=0xE2;
		res[start+1]=0x98;
		res[start+2]=0x82;
		res[start+3]=0xEF;
		res[start+4]=0xB8;
		res[start+5]=0x8F;
		start+=5;
		i+=17;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='E' && chaine[i+9]=='%' && chaine[i+10]=='8' && chaine[i+11]=='3' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x8E;
		res[start+3]=0x83;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='C' && chaine[i+9]=='%' && chaine[i+10]=='B' && chaine[i+11]=='9' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x8C;
		res[start+3]=0xB9;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='C' && chaine[i+9]=='%' && chaine[i+10]=='B' && chaine[i+11]=='B' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x8C;
		res[start+3]=0xBB;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='C' && chaine[i+9]=='%' && chaine[i+10]=='B' && chaine[i+11]=='2' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x8C;
		res[start+3]=0xB2;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='C' && chaine[i+9]=='%' && chaine[i+10]=='B' && chaine[i+11]=='4' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x8C;
		res[start+3]=0xB4;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='C' && chaine[i+9]=='%' && chaine[i+10]=='B' && chaine[i+11]=='5' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x8C;
		res[start+3]=0xB5;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='C' && chaine[i+9]=='%' && chaine[i+10]=='B' && chaine[i+11]=='E' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x8C;
		res[start+3]=0xBE;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='D' && chaine[i+9]=='%' && chaine[i+10]=='8' && chaine[i+11]=='0' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x8D;
		res[start+3]=0x80;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='D' && chaine[i+9]=='%' && chaine[i+10]=='8' && chaine[i+11]=='1' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x8D;
		res[start+3]=0x81;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='D' && chaine[i+9]=='%' && chaine[i+10]=='8' && chaine[i+11]=='4' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x8D;
		res[start+3]=0x84;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='C' && chaine[i+9]=='%' && chaine[i+10]=='9' && chaine[i+11]=='9' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x8C;
		res[start+3]=0x99;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='E' && chaine[i+2]=='2' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='8' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='0' && chaine[i+9]=='%' && chaine[i+10]=='E' && chaine[i+11]=='F' && chaine[i+12]=='%' && chaine[i+13]=='B' && chaine[i+14]=='8' && chaine[i+15]=='%' && chaine[i+16]=='8' && chaine[i+17]=='F' )
		{
		res[start]=0xE2;
		res[start+1]=0x98;
		res[start+2]=0x80;
		res[start+3]=0xEF;
		res[start+4]=0xB8;
		res[start+5]=0x8F;
		start+=5;
		i+=17;
		}
	if(chaine[i]=='%' && chaine[i+1]=='E' && chaine[i+2]=='2' && chaine[i+3]=='%' && chaine[i+4]=='A' && chaine[i+5]=='D' && chaine[i+6]=='%' && chaine[i+7]=='9' && chaine[i+8]=='0' )
		{
		res[start]=0xE2;
		res[start+1]=0xAD;
		res[start+2]=0x90;
		start+=2;
		i+=8;
		}
	if(chaine[i]=='%' && chaine[i+1]=='E' && chaine[i+2]=='2' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='8' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='1' && chaine[i+9]=='%' && chaine[i+10]=='E' && chaine[i+11]=='F' && chaine[i+12]=='%' && chaine[i+13]=='B' && chaine[i+14]=='8' && chaine[i+15]=='%' && chaine[i+16]=='8' && chaine[i+17]=='F' )
		{
		res[start]=0xE2;
		res[start+1]=0x98;
		res[start+2]=0x81;
		res[start+3]=0xEF;
		res[start+4]=0xB8;
		res[start+5]=0x8F;
		start+=5;
		i+=17;
		}
	if(chaine[i]=='%' && chaine[i+1]=='E' && chaine[i+2]=='2' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='B' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='5' )
		{
		res[start]=0xE2;
		res[start+1]=0x9B;
		res[start+2]=0x85;
		start+=2;
		i+=8;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='C' && chaine[i+9]=='%' && chaine[i+10]=='A' && chaine[i+11]=='7' && chaine[i+12]=='%' && chaine[i+13]=='E' && chaine[i+14]=='F' && chaine[i+15]=='%' && chaine[i+16]=='B' && chaine[i+17]=='8' && chaine[i+18]=='%' && chaine[i+19]=='8' && chaine[i+20]=='F' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x8C;
		res[start+3]=0xA7;
		res[start+4]=0xEF;
		res[start+5]=0xB8;
		res[start+6]=0x8F;
		start+=6;
		i+=20;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='C' && chaine[i+9]=='%' && chaine[i+10]=='A' && chaine[i+11]=='8' && chaine[i+12]=='%' && chaine[i+13]=='E' && chaine[i+14]=='F' && chaine[i+15]=='%' && chaine[i+16]=='B' && chaine[i+17]=='8' && chaine[i+18]=='%' && chaine[i+19]=='8' && chaine[i+20]=='F' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x8C;
		res[start+3]=0xA8;
		res[start+4]=0xEF;
		res[start+5]=0xB8;
		res[start+6]=0x8F;
		start+=6;
		i+=20;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='C' && chaine[i+9]=='%' && chaine[i+10]=='8' && chaine[i+11]=='8' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x8C;
		res[start+3]=0x88;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='E' && chaine[i+2]=='2' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='A' && chaine[i+6]=='%' && chaine[i+7]=='A' && chaine[i+8]=='1' )
		{
		res[start]=0xE2;
		res[start+1]=0x9A;
		res[start+2]=0xA1;
		start+=2;
		i+=8;
		}
	if(chaine[i]=='%' && chaine[i+1]=='E' && chaine[i+2]=='2' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='B' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='4' )
		{
		res[start]=0xE2;
		res[start+1]=0x9B;
		res[start+2]=0x84;
		start+=2;
		i+=8;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='9' && chaine[i+8]=='4' && chaine[i+9]=='%' && chaine[i+10]=='A' && chaine[i+11]=='5' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x94;
		res[start+3]=0xA5;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='E' && chaine[i+9]=='%' && chaine[i+10]=='8' && chaine[i+11]=='4' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x8E;
		res[start+3]=0x84;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='E' && chaine[i+2]=='2' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='C' && chaine[i+6]=='%' && chaine[i+7]=='A' && chaine[i+8]=='8' )
		{
		res[start]=0xE2;
		res[start+1]=0x9C;
		res[start+2]=0xA8;
		start+=2;
		i+=8;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='9' && chaine[i+8]=='2' && chaine[i+9]=='%' && chaine[i+10]=='A' && chaine[i+11]=='5' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x92;
		res[start+3]=0xA5;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='D' && chaine[i+9]=='%' && chaine[i+10]=='8' && chaine[i+11]=='7' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x8D;
		res[start+3]=0x87;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='D' && chaine[i+9]=='%' && chaine[i+10]=='8' && chaine[i+11]=='9' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x8D;
		res[start+3]=0x89;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='D' && chaine[i+9]=='%' && chaine[i+10]=='8' && chaine[i+11]=='A' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x8D;
		res[start+3]=0x8A;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='D' && chaine[i+9]=='%' && chaine[i+10]=='8' && chaine[i+11]=='B' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x8D;
		res[start+3]=0x8B;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='D' && chaine[i+9]=='%' && chaine[i+10]=='8' && chaine[i+11]=='C' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x8D;
		res[start+3]=0x8C;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='D' && chaine[i+9]=='%' && chaine[i+10]=='8' && chaine[i+11]=='D' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x8D;
		res[start+3]=0x8D;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='A' && chaine[i+8]=='5' && chaine[i+9]=='%' && chaine[i+10]=='A' && chaine[i+11]=='D' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0xA5;
		res[start+3]=0xAD;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='D' && chaine[i+9]=='%' && chaine[i+10]=='8' && chaine[i+11]=='F' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x8D;
		res[start+3]=0x8F;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='D' && chaine[i+9]=='%' && chaine[i+10]=='9' && chaine[i+11]=='0' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x8D;
		res[start+3]=0x90;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='D' && chaine[i+9]=='%' && chaine[i+10]=='9' && chaine[i+11]=='1' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x8D;
		res[start+3]=0x91;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='D' && chaine[i+9]=='%' && chaine[i+10]=='9' && chaine[i+11]=='2' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x8D;
		res[start+3]=0x92;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='D' && chaine[i+9]=='%' && chaine[i+10]=='9' && chaine[i+11]=='3' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x8D;
		res[start+3]=0x93;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='A' && chaine[i+8]=='5' && chaine[i+9]=='%' && chaine[i+10]=='9' && chaine[i+11]=='D' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0xA5;
		res[start+3]=0x9D;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='D' && chaine[i+9]=='%' && chaine[i+10]=='8' && chaine[i+11]=='5' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x8D;
		res[start+3]=0x85;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='A' && chaine[i+8]=='5' && chaine[i+9]=='%' && chaine[i+10]=='A' && chaine[i+11]=='5' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0xA5;
		res[start+3]=0xA5;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='A' && chaine[i+8]=='5' && chaine[i+9]=='%' && chaine[i+10]=='9' && chaine[i+11]=='1' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0xA5;
		res[start+3]=0x91;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='D' && chaine[i+9]=='%' && chaine[i+10]=='8' && chaine[i+11]=='6' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x8D;
		res[start+3]=0x86;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='A' && chaine[i+8]=='5' && chaine[i+9]=='%' && chaine[i+10]=='9' && chaine[i+11]=='4' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0xA5;
		res[start+3]=0x94;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='A' && chaine[i+8]=='5' && chaine[i+9]=='%' && chaine[i+10]=='9' && chaine[i+11]=='5' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0xA5;
		res[start+3]=0x95;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='C' && chaine[i+9]=='%' && chaine[i+10]=='B' && chaine[i+11]=='D' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x8C;
		res[start+3]=0xBD;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='C' && chaine[i+9]=='%' && chaine[i+10]=='B' && chaine[i+11]=='6' && chaine[i+12]=='%' && chaine[i+13]=='E' && chaine[i+14]=='F' && chaine[i+15]=='%' && chaine[i+16]=='B' && chaine[i+17]=='8' && chaine[i+18]=='%' && chaine[i+19]=='8' && chaine[i+20]=='F' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x8C;
		res[start+3]=0xB6;
		res[start+4]=0xEF;
		res[start+5]=0xB8;
		res[start+6]=0x8F;
		start+=6;
		i+=20;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='A' && chaine[i+8]=='5' && chaine[i+9]=='%' && chaine[i+10]=='9' && chaine[i+11]=='C' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0xA5;
		res[start+3]=0x9C;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='C' && chaine[i+9]=='%' && chaine[i+10]=='B' && chaine[i+11]=='0' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x8C;
		res[start+3]=0xB0;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='D' && chaine[i+9]=='%' && chaine[i+10]=='9' && chaine[i+11]=='E' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x8D;
		res[start+3]=0x9E;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='A' && chaine[i+8]=='5' && chaine[i+9]=='%' && chaine[i+10]=='9' && chaine[i+11]=='0' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0xA5;
		res[start+3]=0x90;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='A' && chaine[i+8]=='7' && chaine[i+9]=='%' && chaine[i+10]=='8' && chaine[i+11]=='0' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0xA7;
		res[start+3]=0x80;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='A' && chaine[i+8]=='5' && chaine[i+9]=='%' && chaine[i+10]=='A' && chaine[i+11]=='9' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0xA5;
		res[start+3]=0xA9;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='D' && chaine[i+9]=='%' && chaine[i+10]=='9' && chaine[i+11]=='4' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x8D;
		res[start+3]=0x94;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='D' && chaine[i+9]=='%' && chaine[i+10]=='9' && chaine[i+11]=='F' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x8D;
		res[start+3]=0x9F;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='D' && chaine[i+9]=='%' && chaine[i+10]=='9' && chaine[i+11]=='5' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x8D;
		res[start+3]=0x95;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='C' && chaine[i+9]=='%' && chaine[i+10]=='A' && chaine[i+11]=='D' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x8C;
		res[start+3]=0xAD;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='A' && chaine[i+8]=='5' && chaine[i+9]=='%' && chaine[i+10]=='9' && chaine[i+11]=='A' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0xA5;
		res[start+3]=0x9A;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='D' && chaine[i+9]=='%' && chaine[i+10]=='B' && chaine[i+11]=='F' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x8D;
		res[start+3]=0xBF;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='D' && chaine[i+9]=='%' && chaine[i+10]=='A' && chaine[i+11]=='6' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x8D;
		res[start+3]=0xA6;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='D' && chaine[i+9]=='%' && chaine[i+10]=='A' && chaine[i+11]=='9' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x8D;
		res[start+3]=0xA9;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='D' && chaine[i+9]=='%' && chaine[i+10]=='A' && chaine[i+11]=='A' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x8D;
		res[start+3]=0xAA;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='E' && chaine[i+9]=='%' && chaine[i+10]=='8' && chaine[i+11]=='2' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x8E;
		res[start+3]=0x82;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='E' && chaine[i+2]=='2' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='8' && chaine[i+6]=='%' && chaine[i+7]=='9' && chaine[i+8]=='5' )
		{
		res[start]=0xE2;
		res[start+1]=0x98;
		res[start+2]=0x95;
		start+=2;
		i+=8;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='D' && chaine[i+9]=='%' && chaine[i+10]=='B' && chaine[i+11]=='7' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x8D;
		res[start+3]=0xB7;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='D' && chaine[i+9]=='%' && chaine[i+10]=='B' && chaine[i+11]=='9' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x8D;
		res[start+3]=0xB9;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='D' && chaine[i+9]=='%' && chaine[i+10]=='B' && chaine[i+11]=='A' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x8D;
		res[start+3]=0xBA;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='A' && chaine[i+8]=='5' && chaine[i+9]=='%' && chaine[i+10]=='8' && chaine[i+11]=='2' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0xA5;
		res[start+3]=0x82;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='9' && chaine[i+8]=='2' && chaine[i+9]=='%' && chaine[i+10]=='A' && chaine[i+11]=='3' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x92;
		res[start+3]=0xA3;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='E' && chaine[i+9]=='%' && chaine[i+10]=='8' && chaine[i+11]=='9' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x8E;
		res[start+3]=0x89;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='E' && chaine[i+9]=='%' && chaine[i+10]=='8' && chaine[i+11]=='1' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x8E;
		res[start+3]=0x81;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='9' && chaine[i+8]=='3' && chaine[i+9]=='%' && chaine[i+10]=='B' && chaine[i+11]=='7' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x93;
		res[start+3]=0xB7;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='9' && chaine[i+8]=='2' && chaine[i+9]=='%' && chaine[i+10]=='A' && chaine[i+11]=='1' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x92;
		res[start+3]=0xA1;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='9' && chaine[i+8]=='2' && chaine[i+9]=='%' && chaine[i+10]=='B' && chaine[i+11]=='0' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x92;
		res[start+3]=0xB0;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='9' && chaine[i+8]=='2' && chaine[i+9]=='%' && chaine[i+10]=='8' && chaine[i+11]=='9' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x92;
		res[start+3]=0x89;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='9' && chaine[i+8]=='2' && chaine[i+9]=='%' && chaine[i+10]=='8' && chaine[i+11]=='A' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x92;
		res[start+3]=0x8A;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='9' && chaine[i+8]=='2' && chaine[i+9]=='%' && chaine[i+10]=='9' && chaine[i+11]=='D' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x92;
		res[start+3]=0x9D;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='9' && chaine[i+8]=='2' && chaine[i+9]=='%' && chaine[i+10]=='9' && chaine[i+11]=='6' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x92;
		res[start+3]=0x96;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='9' && chaine[i+8]=='2' && chaine[i+9]=='%' && chaine[i+10]=='9' && chaine[i+11]=='5' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x92;
		res[start+3]=0x95;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='9' && chaine[i+8]=='2' && chaine[i+9]=='%' && chaine[i+10]=='9' && chaine[i+11]=='4' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x92;
		res[start+3]=0x94;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='E' && chaine[i+9]=='%' && chaine[i+10]=='B' && chaine[i+11]=='5' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x8E;
		res[start+3]=0xB5;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='E' && chaine[i+2]=='2' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='A' && chaine[i+6]=='%' && chaine[i+7]=='A' && chaine[i+8]=='0' && chaine[i+9]=='%' && chaine[i+10]=='E' && chaine[i+11]=='F' && chaine[i+12]=='%' && chaine[i+13]=='B' && chaine[i+14]=='8' && chaine[i+15]=='%' && chaine[i+16]=='8' && chaine[i+17]=='F' )
		{
		res[start]=0xE2;
		res[start+1]=0x9A;
		res[start+2]=0xA0;
		res[start+3]=0xEF;
		res[start+4]=0xB8;
		res[start+5]=0x8F;
		start+=5;
		i+=17;
		}
	if(chaine[i]=='%' && chaine[i+1]=='E' && chaine[i+2]=='2' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='B' && chaine[i+6]=='%' && chaine[i+7]=='9' && chaine[i+8]=='4' )
		{
		res[start]=0xE2;
		res[start+1]=0x9B;
		res[start+2]=0x94;
		start+=2;
		i+=8;
		}
	if(chaine[i]=='%' && chaine[i+1]=='E' && chaine[i+2]=='2' && chaine[i+3]=='%' && chaine[i+4]=='8' && chaine[i+5]=='0' && chaine[i+6]=='%' && chaine[i+7]=='9' && chaine[i+8]=='4' )
		{
		res[start]=0xE2;
		res[start+1]=0x80;
		res[start+2]=0x94;
		start+=2;
		i+=8;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='E' && chaine[i+9]=='%' && chaine[i+10]=='9' && chaine[i+11]=='3' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x8E;
		res[start+3]=0x93;
		start+=3;
		i+=11;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='7' && chaine[i+9]=='%' && chaine[i+10]=='A' && chaine[i+11]=='7' && chaine[i+12]=='%' && chaine[i+13]=='F' && chaine[i+14]=='0' && chaine[i+15]=='%' && chaine[i+16]=='9' && chaine[i+17]=='F' && chaine[i+18]=='%' && chaine[i+19]=='8' && chaine[i+20]=='7' && chaine[i+21]=='%' && chaine[i+22]=='A' && chaine[i+23]=='A' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x87;
		res[start+3]=0xA7;
		res[start+4]=0xF0;
		res[start+5]=0x9F;
		res[start+6]=0x87;
		res[start+7]=0xAA;
		start+=7;
		i+=23;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='7' && chaine[i+9]=='%' && chaine[i+10]=='A' && chaine[i+11]=='7' && chaine[i+12]=='%' && chaine[i+13]=='F' && chaine[i+14]=='0' && chaine[i+15]=='%' && chaine[i+16]=='9' && chaine[i+17]=='F' && chaine[i+18]=='%' && chaine[i+19]=='8' && chaine[i+20]=='7' && chaine[i+21]=='%' && chaine[i+22]=='B' && chaine[i+23]=='7' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x87;
		res[start+3]=0xA7;
		res[start+4]=0xF0;
		res[start+5]=0x9F;
		res[start+6]=0x87;
		res[start+7]=0xB7;
		start+=7;
		i+=23;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='7' && chaine[i+9]=='%' && chaine[i+10]=='A' && chaine[i+11]=='8' && chaine[i+12]=='%' && chaine[i+13]=='F' && chaine[i+14]=='0' && chaine[i+15]=='%' && chaine[i+16]=='9' && chaine[i+17]=='F' && chaine[i+18]=='%' && chaine[i+19]=='8' && chaine[i+20]=='7' && chaine[i+21]=='%' && chaine[i+22]=='A' && chaine[i+23]=='6' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x87;
		res[start+3]=0xA8;
		res[start+4]=0xF0;
		res[start+5]=0x9F;
		res[start+6]=0x87;
		res[start+7]=0xA6;
		start+=7;
		i+=23;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='7' && chaine[i+9]=='%' && chaine[i+10]=='A' && chaine[i+11]=='8' && chaine[i+12]=='%' && chaine[i+13]=='F' && chaine[i+14]=='0' && chaine[i+15]=='%' && chaine[i+16]=='9' && chaine[i+17]=='F' && chaine[i+18]=='%' && chaine[i+19]=='8' && chaine[i+20]=='7' && chaine[i+21]=='%' && chaine[i+22]=='A' && chaine[i+23]=='D' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x87;
		res[start+3]=0xA8;
		res[start+4]=0xF0;
		res[start+5]=0x9F;
		res[start+6]=0x87;
		res[start+7]=0xAD;
		start+=7;
		i+=23;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='7' && chaine[i+9]=='%' && chaine[i+10]=='A' && chaine[i+11]=='8' && chaine[i+12]=='%' && chaine[i+13]=='F' && chaine[i+14]=='0' && chaine[i+15]=='%' && chaine[i+16]=='9' && chaine[i+17]=='F' && chaine[i+18]=='%' && chaine[i+19]=='8' && chaine[i+20]=='7' && chaine[i+21]=='%' && chaine[i+22]=='B' && chaine[i+23]=='3' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x87;
		res[start+3]=0xA8;
		res[start+4]=0xF0;
		res[start+5]=0x9F;
		res[start+6]=0x87;
		res[start+7]=0xB3;
		start+=7;
		i+=23;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='7' && chaine[i+9]=='%' && chaine[i+10]=='A' && chaine[i+11]=='9' && chaine[i+12]=='%' && chaine[i+13]=='F' && chaine[i+14]=='0' && chaine[i+15]=='%' && chaine[i+16]=='9' && chaine[i+17]=='F' && chaine[i+18]=='%' && chaine[i+19]=='8' && chaine[i+20]=='7' && chaine[i+21]=='%' && chaine[i+22]=='A' && chaine[i+23]=='A' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x87;
		res[start+3]=0xA9;
		res[start+4]=0xF0;
		res[start+5]=0x9F;
		res[start+6]=0x87;
		res[start+7]=0xAA;
		start+=7;
		i+=23;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='7' && chaine[i+9]=='%' && chaine[i+10]=='A' && chaine[i+11]=='9' && chaine[i+12]=='%' && chaine[i+13]=='F' && chaine[i+14]=='0' && chaine[i+15]=='%' && chaine[i+16]=='9' && chaine[i+17]=='F' && chaine[i+18]=='%' && chaine[i+19]=='8' && chaine[i+20]=='7' && chaine[i+21]=='%' && chaine[i+22]=='B' && chaine[i+23]=='0' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x87;
		res[start+3]=0xA9;
		res[start+4]=0xF0;
		res[start+5]=0x9F;
		res[start+6]=0x87;
		res[start+7]=0xB0;
		start+=7;
		i+=23;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='7' && chaine[i+9]=='%' && chaine[i+10]=='A' && chaine[i+11]=='9' && chaine[i+12]=='%' && chaine[i+13]=='F' && chaine[i+14]=='0' && chaine[i+15]=='%' && chaine[i+16]=='9' && chaine[i+17]=='F' && chaine[i+18]=='%' && chaine[i+19]=='8' && chaine[i+20]=='7' && chaine[i+21]=='%' && chaine[i+22]=='B' && chaine[i+23]=='F' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x87;
		res[start+3]=0xA9;
		res[start+4]=0xF0;
		res[start+5]=0x9F;
		res[start+6]=0x87;
		res[start+7]=0xBF;
		start+=7;
		i+=23;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='7' && chaine[i+9]=='%' && chaine[i+10]=='A' && chaine[i+11]=='A' && chaine[i+12]=='%' && chaine[i+13]=='F' && chaine[i+14]=='0' && chaine[i+15]=='%' && chaine[i+16]=='9' && chaine[i+17]=='F' && chaine[i+18]=='%' && chaine[i+19]=='8' && chaine[i+20]=='7' && chaine[i+21]=='%' && chaine[i+22]=='B' && chaine[i+23]=='8' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x87;
		res[start+3]=0xAA;
		res[start+4]=0xF0;
		res[start+5]=0x9F;
		res[start+6]=0x87;
		res[start+7]=0xB8;
		start+=7;
		i+=23;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='7' && chaine[i+9]=='%' && chaine[i+10]=='A' && chaine[i+11]=='A' && chaine[i+12]=='%' && chaine[i+13]=='F' && chaine[i+14]=='0' && chaine[i+15]=='%' && chaine[i+16]=='9' && chaine[i+17]=='F' && chaine[i+18]=='%' && chaine[i+19]=='8' && chaine[i+20]=='7' && chaine[i+21]=='%' && chaine[i+22]=='B' && chaine[i+23]=='A' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x87;
		res[start+3]=0xAA;
		res[start+4]=0xF0;
		res[start+5]=0x9F;
		res[start+6]=0x87;
		res[start+7]=0xBA;
		start+=7;
		i+=23;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='7' && chaine[i+9]=='%' && chaine[i+10]=='A' && chaine[i+11]=='B' && chaine[i+12]=='%' && chaine[i+13]=='F' && chaine[i+14]=='0' && chaine[i+15]=='%' && chaine[i+16]=='9' && chaine[i+17]=='F' && chaine[i+18]=='%' && chaine[i+19]=='8' && chaine[i+20]=='7' && chaine[i+21]=='%' && chaine[i+22]=='A' && chaine[i+23]=='E' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x87;
		res[start+3]=0xAB;
		res[start+4]=0xF0;
		res[start+5]=0x9F;
		res[start+6]=0x87;
		res[start+7]=0xAE;
		start+=7;
		i+=23;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='7' && chaine[i+9]=='%' && chaine[i+10]=='A' && chaine[i+11]=='C' && chaine[i+12]=='%' && chaine[i+13]=='F' && chaine[i+14]=='0' && chaine[i+15]=='%' && chaine[i+16]=='9' && chaine[i+17]=='F' && chaine[i+18]=='%' && chaine[i+19]=='8' && chaine[i+20]=='7' && chaine[i+21]=='%' && chaine[i+22]=='A' && chaine[i+23]=='7' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x87;
		res[start+3]=0xAC;
		res[start+4]=0xF0;
		res[start+5]=0x9F;
		res[start+6]=0x87;
		res[start+7]=0xA7;
		start+=7;
		i+=23;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='7' && chaine[i+9]=='%' && chaine[i+10]=='A' && chaine[i+11]=='C' && chaine[i+12]=='%' && chaine[i+13]=='F' && chaine[i+14]=='0' && chaine[i+15]=='%' && chaine[i+16]=='9' && chaine[i+17]=='F' && chaine[i+18]=='%' && chaine[i+19]=='8' && chaine[i+20]=='7' && chaine[i+21]=='%' && chaine[i+22]=='B' && chaine[i+23]=='7' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x87;
		res[start+3]=0xAC;
		res[start+4]=0xF0;
		res[start+5]=0x9F;
		res[start+6]=0x87;
		res[start+7]=0xB7;
		start+=7;
		i+=23;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='7' && chaine[i+9]=='%' && chaine[i+10]=='A' && chaine[i+11]=='E' && chaine[i+12]=='%' && chaine[i+13]=='F' && chaine[i+14]=='0' && chaine[i+15]=='%' && chaine[i+16]=='9' && chaine[i+17]=='F' && chaine[i+18]=='%' && chaine[i+19]=='8' && chaine[i+20]=='7' && chaine[i+21]=='%' && chaine[i+22]=='A' && chaine[i+23]=='A' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x87;
		res[start+3]=0xAE;
		res[start+4]=0xF0;
		res[start+5]=0x9F;
		res[start+6]=0x87;
		res[start+7]=0xAA;
		start+=7;
		i+=23;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='7' && chaine[i+9]=='%' && chaine[i+10]=='A' && chaine[i+11]=='E' && chaine[i+12]=='%' && chaine[i+13]=='F' && chaine[i+14]=='0' && chaine[i+15]=='%' && chaine[i+16]=='9' && chaine[i+17]=='F' && chaine[i+18]=='%' && chaine[i+19]=='8' && chaine[i+20]=='7' && chaine[i+21]=='%' && chaine[i+22]=='B' && chaine[i+23]=='1' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x87;
		res[start+3]=0xAE;
		res[start+4]=0xF0;
		res[start+5]=0x9F;
		res[start+6]=0x87;
		res[start+7]=0xB1;
		start+=7;
		i+=23;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='7' && chaine[i+9]=='%' && chaine[i+10]=='A' && chaine[i+11]=='E' && chaine[i+12]=='%' && chaine[i+13]=='F' && chaine[i+14]=='0' && chaine[i+15]=='%' && chaine[i+16]=='9' && chaine[i+17]=='F' && chaine[i+18]=='%' && chaine[i+19]=='8' && chaine[i+20]=='7' && chaine[i+21]=='%' && chaine[i+22]=='B' && chaine[i+23]=='9' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x87;
		res[start+3]=0xAE;
		res[start+4]=0xF0;
		res[start+5]=0x9F;
		res[start+6]=0x87;
		res[start+7]=0xB9;
		start+=7;
		i+=23;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='7' && chaine[i+9]=='%' && chaine[i+10]=='A' && chaine[i+11]=='F' && chaine[i+12]=='%' && chaine[i+13]=='F' && chaine[i+14]=='0' && chaine[i+15]=='%' && chaine[i+16]=='9' && chaine[i+17]=='F' && chaine[i+18]=='%' && chaine[i+19]=='8' && chaine[i+20]=='7' && chaine[i+21]=='%' && chaine[i+22]=='B' && chaine[i+23]=='5' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x87;
		res[start+3]=0xAF;
		res[start+4]=0xF0;
		res[start+5]=0x9F;
		res[start+6]=0x87;
		res[start+7]=0xB5;
		start+=7;
		i+=23;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='7' && chaine[i+9]=='%' && chaine[i+10]=='B' && chaine[i+11]=='0' && chaine[i+12]=='%' && chaine[i+13]=='F' && chaine[i+14]=='0' && chaine[i+15]=='%' && chaine[i+16]=='9' && chaine[i+17]=='F' && chaine[i+18]=='%' && chaine[i+19]=='8' && chaine[i+20]=='7' && chaine[i+21]=='%' && chaine[i+22]=='B' && chaine[i+23]=='7' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x87;
		res[start+3]=0xB0;
		res[start+4]=0xF0;
		res[start+5]=0x9F;
		res[start+6]=0x87;
		res[start+7]=0xB7;
		start+=7;
		i+=23;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='7' && chaine[i+9]=='%' && chaine[i+10]=='B' && chaine[i+11]=='3' && chaine[i+12]=='%' && chaine[i+13]=='F' && chaine[i+14]=='0' && chaine[i+15]=='%' && chaine[i+16]=='9' && chaine[i+17]=='F' && chaine[i+18]=='%' && chaine[i+19]=='8' && chaine[i+20]=='7' && chaine[i+21]=='%' && chaine[i+22]=='B' && chaine[i+23]=='4' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x87;
		res[start+3]=0xB3;
		res[start+4]=0xF0;
		res[start+5]=0x9F;
		res[start+6]=0x87;
		res[start+7]=0xB4;
		start+=7;
		i+=23;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='7' && chaine[i+9]=='%' && chaine[i+10]=='B' && chaine[i+11]=='5' && chaine[i+12]=='%' && chaine[i+13]=='F' && chaine[i+14]=='0' && chaine[i+15]=='%' && chaine[i+16]=='9' && chaine[i+17]=='F' && chaine[i+18]=='%' && chaine[i+19]=='8' && chaine[i+20]=='7' && chaine[i+21]=='%' && chaine[i+22]=='B' && chaine[i+23]=='9' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x87;
		res[start+3]=0xB5;
		res[start+4]=0xF0;
		res[start+5]=0x9F;
		res[start+6]=0x87;
		res[start+7]=0xB9;
		start+=7;
		i+=23;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='7' && chaine[i+9]=='%' && chaine[i+10]=='B' && chaine[i+11]=='7' && chaine[i+12]=='%' && chaine[i+13]=='F' && chaine[i+14]=='0' && chaine[i+15]=='%' && chaine[i+16]=='9' && chaine[i+17]=='F' && chaine[i+18]=='%' && chaine[i+19]=='8' && chaine[i+20]=='7' && chaine[i+21]=='%' && chaine[i+22]=='B' && chaine[i+23]=='A' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x87;
		res[start+3]=0xB7;
		res[start+4]=0xF0;
		res[start+5]=0x9F;
		res[start+6]=0x87;
		res[start+7]=0xBA;
		start+=7;
		i+=23;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='7' && chaine[i+9]=='%' && chaine[i+10]=='B' && chaine[i+11]=='8' && chaine[i+12]=='%' && chaine[i+13]=='F' && chaine[i+14]=='0' && chaine[i+15]=='%' && chaine[i+16]=='9' && chaine[i+17]=='F' && chaine[i+18]=='%' && chaine[i+19]=='8' && chaine[i+20]=='7' && chaine[i+21]=='%' && chaine[i+22]=='A' && chaine[i+23]=='A' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x87;
		res[start+3]=0xB8;
		res[start+4]=0xF0;
		res[start+5]=0x9F;
		res[start+6]=0x87;
		res[start+7]=0xAA;
		start+=7;
		i+=23;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='7' && chaine[i+9]=='%' && chaine[i+10]=='B' && chaine[i+11]=='8' && chaine[i+12]=='%' && chaine[i+13]=='F' && chaine[i+14]=='0' && chaine[i+15]=='%' && chaine[i+16]=='9' && chaine[i+17]=='F' && chaine[i+18]=='%' && chaine[i+19]=='8' && chaine[i+20]=='7' && chaine[i+21]=='%' && chaine[i+22]=='B' && chaine[i+23]=='3' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x87;
		res[start+3]=0xB8;
		res[start+4]=0xF0;
		res[start+5]=0x9F;
		res[start+6]=0x87;
		res[start+7]=0xB3;
		start+=7;
		i+=23;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='7' && chaine[i+9]=='%' && chaine[i+10]=='B' && chaine[i+11]=='9' && chaine[i+12]=='%' && chaine[i+13]=='F' && chaine[i+14]=='0' && chaine[i+15]=='%' && chaine[i+16]=='9' && chaine[i+17]=='F' && chaine[i+18]=='%' && chaine[i+19]=='8' && chaine[i+20]=='7' && chaine[i+21]=='%' && chaine[i+22]=='B' && chaine[i+23]=='7' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x87;
		res[start+3]=0xB9;
		res[start+4]=0xF0;
		res[start+5]=0x9F;
		res[start+6]=0x87;
		res[start+7]=0xB7;
		start+=7;
		i+=23;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='7' && chaine[i+9]=='%' && chaine[i+10]=='B' && chaine[i+11]=='A' && chaine[i+12]=='%' && chaine[i+13]=='F' && chaine[i+14]=='0' && chaine[i+15]=='%' && chaine[i+16]=='9' && chaine[i+17]=='F' && chaine[i+18]=='%' && chaine[i+19]=='8' && chaine[i+20]=='7' && chaine[i+21]=='%' && chaine[i+22]=='B' && chaine[i+23]=='3' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x87;
		res[start+3]=0xBA;
		res[start+4]=0xF0;
		res[start+5]=0x9F;
		res[start+6]=0x87;
		res[start+7]=0xB3;
		start+=7;
		i+=23;
		}
	if(chaine[i]=='%' && chaine[i+1]=='F' && chaine[i+2]=='0' && chaine[i+3]=='%' && chaine[i+4]=='9' && chaine[i+5]=='F' && chaine[i+6]=='%' && chaine[i+7]=='8' && chaine[i+8]=='7' && chaine[i+9]=='%' && chaine[i+10]=='B' && chaine[i+11]=='A' && chaine[i+12]=='%' && chaine[i+13]=='F' && chaine[i+14]=='0' && chaine[i+15]=='%' && chaine[i+16]=='9' && chaine[i+17]=='F' && chaine[i+18]=='%' && chaine[i+19]=='8' && chaine[i+20]=='7' && chaine[i+21]=='%' && chaine[i+22]=='B' && chaine[i+23]=='8' )
		{
		res[start]=0xF0;
		res[start+1]=0x9F;
		res[start+2]=0x87;
		res[start+3]=0xBA;
		res[start+4]=0xF0;
		res[start+5]=0x9F;
		res[start+6]=0x87;
		res[start+7]=0xB8;
		start+=7;
		i+=23;
		}
	start++;
	i++;
	}
while(i<=strlen(chaine));
strcpy(chaine,res);
free(res);
}

char* read_POST() 
{
query_size=atoi(getenv("CONTENT_LENGTH"));
char* query_string = (char*) malloc(query_size);
if (query_string != NULL) fread(query_string,query_size,1,stdin);
return query_string;
}

int max_getchaine(char *chaine)
{
int i,somme;

somme=0;
for(i=0;i<strlen(chaine);i++)
	{
	if(chaine[i]=='=') somme++;
	}
return(somme);
}

int get_chaine(char *chaine,int pos,char *resultat)
{
int i,n,start;

i=strlen(chaine);
for(n=0; n<pos;n++) 
	{
	while(chaine[i]!='=') i--;
	i--;
	}
i+=2;
start=i;
do
	{
	resultat[i-start]=chaine[i];
	i++;
	}
while(chaine[i-1]!=0 && chaine[i-1]!='&');
resultat[i-start-1]=0;
}

int get_chaine2(char *chaine,int pos,char *resultat)
{
int i,n,start;

i=strlen(chaine);
for(n=0; n<pos;n++) 
	{
	while(chaine[i]!='&' && i>=0) i--;
	i--;
	}
i+=2;
start=i;
do
	{
	resultat[i-start]=chaine[i];
	i++;
	}
while(chaine[i-1]!=0 && chaine[i-1]!='=');
resultat[i-start-1]=0;
}

void klog(char *ph)
{
int fd;
char a;

a='\n';
fd=open("/tmp/res",O_CREAT|O_WRONLY,0644);
write(fd,ph,strlen(ph));
write(fd,&a,1);
close(fd);
}

void tamb(char *avatar)
{
int i;

for(i=0;i<strlen(avatar);i++)
	{
	if(avatar[i]=='+') avatar[i]=' ';
	}
url_decode(avatar);
prepare_contenu(avatar);
}