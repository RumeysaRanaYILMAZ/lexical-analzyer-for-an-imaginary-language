#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define KEY 9
#define ALPHA 53
#define NUM 10
char nums[NUM]="0123456789";
char alphabet[ALPHA]="abcdefghijklmnopqrstuvwxyz_ABCDEFGHIJKLMNOPQRSTUVWXYZ";
char keywords[KEY][6]={"sub","add","to","from","out","move","loop","times","int"};
typedef struct obj{//taranan charlar objectlerin içinde tutulur yeni bir tipte char topluluðu  bulununca yeni object oluþturulur.
char *el;
int size;
}object;

bool exist(char a[],char t,int size){//gönderilen charýn istenilen tiple olup olmadýðýný kontrol eder.
    bool result=false;
    for (int i=0;i<size;++i){
    if(a[i]==t){
        result=true;
        break;
        }
    }
    return result;
}
char * cls(char c){ //gönderilen charýn tipini belirleyip atama yapar
    if(exist(alphabet,c,ALPHA)){
        return "karakter";
    }else if(exist(nums,c,NUM)){
        return "sayi";
    }else{
        switch(c){
            case '-':
                return "minus";
            case '.':
                return "end of line";
            case '=':
                return "assign";
            case '"':
                return "string";
            case '(':
                return "open_parenthesis";
            case ')':
                return "close_parenthesis";
            case '{':
                return "comment";
            case '}':
                return "comment";
            case ' ':
                return "blank";
            case ',':
                return "comma";
            case '[':
                return "open_bracket";
            case ']':
                return "close_bracket";
            case '\n':
                return "new_line";
            default:
                return "error";
        }
    }
}
object * init_obj(char tt){ //obje oluþturulur.
    object *ne;
    ne=(object *)malloc(sizeof(object));
    (*ne).el=(char *)calloc(1,sizeof(char));
    *(*ne).el=tt;
    (*ne).size=1;
    return ne;
}
void copyy(char dest[],char *src){
    int y=0;
    while(src[y]!='\0'){
        dest[y]=src[y];
        ++y;
    }
}
int comp(char s[],char *t){
    int cp=0;
    bool eq=1;
    while(cp<strlen(t)){
        if(s[cp]!=t[cp]){
            eq=0;
            break;
        }
        cp++;
    }
    return eq;
}
int ascii(char *p,char*l){
    int toplam=0;
    int fark;
    for(int i=0;i<strlen(p);++i){
        fark=p[i]-l[i];
        toplam+=fark;
    }
    return toplam;
}
void swapp(char listt[],int index1,int index2){
    char buff=listt[index1];
    listt[index1]=index2;
    listt[index2]=buff;
}
int key(char *p){ //keyword olup olmadýðý kontrol edilir.
    int exist=0;
    for(int i=0;i<KEY;++i){
        char *l=keywords[i];
        if(comp(p,l)==1){
            exist=1;
            break;
        }
    }
    return exist;
}
void extend_el(object *py,char t){ //yeni charlar okudukça ayný tipte ise objelere eklenir.
    int new_len=(*py).size+1;
    char *buff;
    buff=(char *)calloc(new_len,sizeof(char));
    for(int i=0;i<new_len-1;i++){
        buff[i]=(*py).el[i];
    }
    buff[new_len-1]=t;
    free((*py).el);
    (*py).el=buff;
    (*py).size=new_len;
    }
typedef struct list{ //objelerin tutulduðu linked list.
object *element;
char type[20];
struct list *next;
char explanation[100];
}nod;
nod * init_list(char cursor,char tip[]){ //liste oluþturma
    nod * root;
    root=(nod *)malloc(sizeof(nod));
    (*root).element=init_obj(cursor);
    root->next=NULL;
    strcpy((*root).type,tip);
    return root;
}
nod * add(char cursor,nod *ls){ //node ekleme
    nod *nww;
    char *t;
    t=cls(cursor);
    nww=(nod *)malloc(sizeof(nod));
    (*nww).element=init_obj(cursor);
    strcpy((*nww).type,t);
    (*ls).next=nww;
    return nww;
}
void delete_all(nod *ls){
    free((void *)ls);
}
int main()
{
    char w[200];
    char r[200];
    printf("reading file:");
    scanf("%s", r);
    printf("writing file:");
    scanf("%s", w);
    FILE *read,*write;
    write=fopen(w,"w");
    read=fopen(r,"r");
    char ch;
    int f=0;
    char *toplam;
    int key_num=0;
    int idf_num=0;
    int par_num=0;
    int end_num=0;
    while((ch = fgetc(read)) != EOF){//dosyadan okunan kod pointer arraye atýlýr.
        if(ch=='{'){
            do{
            }while((ch = fgetc(read))!='}');
        }else{
            ++f;
            char *buff;
            buff=(char *)calloc(f,sizeof(char));
            for(int i=0;i<f-1;i++){
                buff[i]=toplam[i];
            }
            buff[f-1]=ch;
            free(toplam);
            toplam=buff;
            }
    }
    ch=' ';
    char *p,*last;
    p=cls(ch);
    last=p;
    nod *head,*crsr;
    head=init_list(ch,p);
    crsr=head;
    int size=1;
    int hareket=0;
    char *keyw="keyword";
    char *id="identifier";
    while(hareket<f){
        ch=toplam[hareket];
        p=cls(ch);
        if((exist(alphabet,toplam[hareket],ALPHA))){
            object *ky;
            ky=init_obj(ch);
            while(true){
                if((*ky).size>20){ //identifier uzunluk kontrolu yapýlýr.
                    crsr=add('#',crsr);
                    (*(*crsr).element).el=(*ky).el;
                    char *err="exceeded identifier length limit";
                    copyy((*crsr).explanation,err);
                    ch=toplam[++hareket];
                    break;
                }else{
                    if(key((*ky).el)){//identifier ve keyword ayrýmý yapýlýr.
                        if((exist(alphabet,toplam[hareket+1],ALPHA))|| exist(nums,toplam[hareket+1],NUM)){
                            while((exist(alphabet,toplam[hareket+1],ALPHA)) || exist(nums,toplam[hareket+1],NUM)){
                                extend_el(ky,ch);
                                ch=toplam[++hareket];
                            }
                            if((*ky).size>20){
                                crsr=add('#',crsr);
                                (*(*crsr).element).el=(*ky).el;
                                char *err="exceeded identifier length limit";
                                copyy((*crsr).explanation,err);
                                ch=toplam[++hareket];
                                break;
                            }else{
                                crsr=add('0',crsr);
                                *(*crsr).element=*ky;
                                p=id;
                                ++idf_num;
                                copyy((*crsr).type,id);
                                ch=toplam[++hareket];
                                break;
                            }
                        }else{
                            crsr=add('0',crsr);
                            *(*crsr).element=*ky;
                            p=keyw;
                            ++key_num;
                            copyy((*crsr).type,keyw);
                            ch=toplam[++hareket];
                            break;
                        }
                    }else{
                        if(((exist(alphabet,toplam[hareket+1],ALPHA))|| exist(nums,toplam[hareket+1],NUM))){
                            ch=toplam[++hareket];
                            extend_el(ky,ch);
                        }else{
                                crsr=add('0',crsr);
                                *(*crsr).element=*ky;
                                p=id;
                                ++idf_num;
                                copyy((*crsr).type,id);
                                ch=toplam[++hareket];
                                break;
                        }
                    }
                }
            }
            ++size;
        }else if(exist(nums,toplam[hareket],NUM)){
            crsr=add(toplam[hareket],crsr);
            while(toplam[hareket+1]!=' '){
                    ch=toplam[++hareket];
                    extend_el((*crsr).element,ch);
                if(!exist(nums,toplam[hareket+1],NUM)){
                    object *kt;
                    kt=init_obj('#');
                    (*kt).el=(*(*crsr).element).el;
                    crsr=add('#',crsr);
                    *(*crsr).element=*kt;
                    char *err="incompatible type";
                    copyy((*crsr).explanation,err);
                    break;
                }
            }
            ch=toplam[++hareket];
        }else if(ch=='-'){//izin verilmeyen operationlarýn kontrolü yapýlýr.
            if(exist(nums,toplam[hareket+1],NUM)){
                crsr=add('0',crsr);
                *(*(*crsr).element).el='-';
                p="sayi";
                last=p;
                ch=toplam[++hareket];
            }else if(toplam[hareket+1]=='-'){
                crsr=add('#',crsr);
                (*(*crsr).element).el="--";
                char *err="only one minus sign allowed";
                copyy((*crsr).explanation,err);
                ch=toplam[++hareket];
            }else{
                crsr=add('#',crsr);
                char *err="minus can't use without number";
                copyy((*crsr).explanation,err);
                ch=toplam[++hareket];
            }
        }
        else if(ch=='"'){//string baþlangýcýný belirtir diðer týrnak görülene kadar buffer string ile doldurulur.
            crsr=add('"',crsr);
            while((ch=toplam[++hareket]) !='"'){
                    extend_el((*crsr).element,ch);
                }
            extend_el((*crsr).element,ch);
            ch=toplam[++hareket];
        }else{
            if(strcmp(last,p)==0){
                extend_el((*crsr).element,ch);
                ++hareket;
            }else{
                if(ch=='.'){
                    ++end_num;
                }else if(ch=='(' || ch==')'){
                    ++par_num;
                }
                last=p;
                crsr=add(ch,crsr);
                ++hareket;
            }
        }
    }
    fclose(read);

    struct list *tt=(*head).next;// Analiz sonuçlarý dosyaya yazýlýr.
    char *errr="error";
    int err_exist=0;
    while(tt!=NULL){
        if(strcmp((*tt).type,errr)==0){
            printf("%s\t%s\t%s\n",(*tt).type,(*tt).explanation,(*(*tt).element).el);
            err_exist=1;
        }
        tt=(*tt).next;
    }
    tt=(*head).next;
    while(tt!=NULL && err_exist==0){
        if(*(*(*tt).element).el=='\n'){
            fprintf(write,"\n");
            tt=(*tt).next;
        }else{
            fprintf(write,"<%s,%s>",(*tt).type,(*(*tt).element).el);
            tt=(*tt).next;
        }
    }
    if(err_exist==0){
        printf("keyword number:%d\n",key_num);
        printf("identifier number:%d\n",idf_num);
        printf("paranthesis number:%d\n",par_num);
        printf("end of line number:%d\n",end_num);
    }

    fclose(write);
    return 0;
}
