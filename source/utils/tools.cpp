#include <utils/tools.h>
// tools
#include <public/vars.h>
#include <regex>
#include <netdb.h>
#include <arpa/inet.h>
#include <iostream>
#include<unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/socket.h>
std::string read_file(std::string file_path){
    std::ifstream in(file_path);
    std::ostringstream tmp;
    tmp << in.rdbuf();
    return tmp.str();
}
std::vector<std::string> ls(std::string path){
    std::vector<std::string> temp;
    DIR *dir = opendir(path.c_str());
    struct dirent *dp;
    while((dp=readdir(dir))!=NULL){
        if(dp->d_name != std::string(".") and dp->d_name != std::string("..")){
            temp.push_back(dp->d_name);
        }
    }
    closedir(dir);
    return temp;
}

void c_mkdir(std::string path){
    mkdir(path.c_str(),0775);
}

void check_error(int status){
    if(status!=0){
        exit(-99);
    }
}

void log(std::string msg){
    std::cout<<msg<<std::endl;
}




bool FileExists(std::string path)
{
    struct stat fileStat; 
    if ( stat(path.c_str(), &fileStat) )
    {
        return false;
    }
    if ( !S_ISREG(fileStat.st_mode) )
    {
        return false;
    }
    return true;
}

bool DirExists(std::string path)
{
    struct stat fileStat;
    if ( stat(path.c_str(), &fileStat) )
    {
        return false;
    }
    if ( !S_ISDIR(fileStat.st_mode) )
    {
        return false;
    }
    return true;
}

std::vector<std::string> split(std::string s, std::string d) { 
	std::string text = s;
	std::regex ws_re(d); 
	// whitespace 
	std::vector<std::string> tokens(std::sregex_token_iterator(text.begin(), text.end(), ws_re, -1), std::sregex_token_iterator()); 
	return tokens;
}
std::vector<std::string> readlines_fromfile(std::string file_path){
    std::vector<std::string> temp;
    std::string query;
    std::ifstream in(file_path);
    while (getline(in,query))
    {
        temp.push_back(query);
    }
    return temp;
}

void DOWNLOAD(std::string url,std::string file_path){
        // fisrt;
        std::smatch results;
        std::smatch sm;
        std::regex p("(https?)://(.*?)(/.+)");
        if(std::regex_match(url,results,p)){
            int sfd = socket(AF_INET,SOCK_STREAM,0);
            struct sockaddr_in  server_addr;  
            int port;
            std::string head=(
                    "HEAD "+std::string(results[3])+" "+HTTP_VERSION+HTTP_DELIM
                    +"Host: "+std::string(results[2])+HTTP_DELIM
                    +"User-Agent: Ccao Star Getter"+HTTP_DELIM
                    +"Accept: */*"+HTTP_DELIM
                    +"Connection: close"+HTTP_DELIM
                    +HTTP_DELIM
                );
            
            if(std::string(results[1])=="https"){
                // https
            }else{
                // http
                
                std::regex sp("(.*?):(.+)");
                std::string _ = results[2];
                if(std::regex_match(_,sm,sp)){
                    port=std::stoi(sm[2]);
                }else{
                    port=80;
                }
            }
            bzero(&server_addr, sizeof(server_addr));  
            server_addr.sin_family = AF_INET;  
            server_addr.sin_port = htons(port);
            // server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
            // connect(server_addr,(struct sockaddr *)&server_addr)
            std::string d_ip = sm[1];
            inet_aton(getipbydomain(d_ip).c_str(), &server_addr.sin_addr);
            socklen_t server_addr_length = sizeof(server_addr); 

            if(connect(sfd, (struct sockaddr*)&server_addr, server_addr_length)<0){
                exit(1);
            }else{
                char data[1024];
                memset(data,0,sizeof(data));
                send(sfd,head.c_str(),strlen(head.c_str()),0);
                recv(sfd,data,sizeof(data),0);
                std::string cc = data;
                std::regex p("\\r\\nContent-Length: (.*?)\\r\\n");
                std::smatch sdcw;
                close(sfd);
                if(std::regex_search(cc,sdcw,p)){
                    long long int size = std::stol(sdcw[1]);
                        int nsfd = socket(AF_INET,SOCK_STREAM,0);
                        struct sockaddr_in  nserver_addr;  
                        bzero(&server_addr, sizeof(server_addr));  
                        nserver_addr.sin_family = AF_INET;  
                        nserver_addr.sin_port = htons(port);
                        inet_aton(getipbydomain(d_ip).c_str(), &nserver_addr.sin_addr);

                    connect(nsfd, (struct sockaddr*)&nserver_addr, server_addr_length);
                    head=(
                    "GET "+std::string(results[3])+" "+HTTP_VERSION+HTTP_DELIM
                    +"Host: "+std::string(results[2])+HTTP_DELIM
                    +"User-Agent: Ccao Star Getter"+HTTP_DELIM
                    +"Accept: */*"+HTTP_DELIM
                    +"Connection: close"+HTTP_DELIM
                    +HTTP_DELIM
                    );
                    char temp[1024];
                    FILE *fp = fopen(file_path.c_str(),"w");
                    send(nsfd,head.c_str(),strlen(head.c_str()),0);
                    int i;
                    long int total=0;
                    // fuck head
                    char ch;
                    int trecv;
                    while((trecv=recv(nsfd,&ch,1,0))>0){
                        if(ch=='\r'){
                            trecv=recv(nsfd,&ch,1,0);
                            if(trecv>0 and ch =='\n'){
                                trecv=recv(nsfd,&ch,1,0);
                                if(trecv>0 and ch =='\r'){
                                    trecv=recv(nsfd,&ch,1,0);
                                    if(trecv>0 and ch =='\n'){
                                        break;
                                    }
                                }
                            }
                        }
                    }
                    for(;;){
                        // /r/n/r/n 连续两个
                        if(i>0){
                            i=recv(nsfd,temp,1024,0);
                            total+=i;
                            fwrite(temp,i,1,fp);
                            progress_bar((long int)total,size);
                        }else{
                            //LOG(std::to_string(i));
                            break;
                        }
                        
                    }

                    fflush(fp);
                    fclose(fp);
                    close(nsfd);
                }else{
                }


            }
        }else{
            std::cout<<"not a http request ! "<<std::endl;
        }



        // http://asdasdasddsa:80/123123123
    //     my_addr.sin_family = AF_INET; /* host byte order */
    // 　　 my_addr.sin_port = htons(MYPORT); /* short, network byte order */
    // 　　 my_addr.sin_addr.s_addr = inet_addr("132.241.5.10");
}
std::string getipbydomain(std::string domain){
    struct in_addr **addr_list;
    struct hostent *he = gethostbyname(domain.c_str());
    addr_list = (struct in_addr **)he->h_addr_list;
    return std::string(inet_ntoa(*addr_list[0]));
}
void progress_bar(long int x,long int total)
{
    int i;
    char tmp[100] = {0};
    static int x_old = 0;
    double cc = (double)x/(double)(total);
    int s;
    s = (int)(100.0*cc);
    if(s == x_old)
    {
        return;
    }
    x_old = s;
    i = s/2;
    if(i > 50)
        i = 50;
    memset(tmp, '-', i);
    tmp[i]='>';
    printf("\r%d%|%s|", s, tmp);
    fflush(stdout);//立刻输出
}