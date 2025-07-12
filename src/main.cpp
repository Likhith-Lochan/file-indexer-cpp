#include "indexer.hpp"
#include <iostream>

int main(int argc,char* argv[]){

    if(argc<2){
        std::cout<<"Usage : ./indexer <path> [pattern] [--regex]\n";
        return 1;
    }

    std::string root=argv[1];
    std::string pattern= argc>=3?argv[2]:"*";
    bool use_regex = argc == 4 && std::string(argv[3])== "--regex";

    int thread_count=std::thread::hardware_concurrency();
    if(thread_count==0)thread_count=4;

    FileIndexer indexer(root,thread_count);
    indexer.start();

    std::vector<FileEntry> results=indexer.search(pattern,use_regex);
    for(size_t i=0;i<results.size();i++){
        std::cout<<results[i].path<<"("<<results[i].size<<" bytes)\n";
    }

    std::cout<<"Found "<<results.size()<<" matching files. \n";
    return 0;
}