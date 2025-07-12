#include "indexer.hpp"
#include <regex>
#include <fnmatch.h>


std::vector<FileEntry> FileIndexer::search(const std::string& pattern,bool use_regex){
    std::vector<FileEntry> results;

    std::lock_guard<std::mutex> lock(result_mutex);

    for(size_t i=0;i<indexed_files.size();++i){
        const auto& file=indexed_files[i];

        if(use_regex){
            try
            {
                std::regex re(pattern);
                if(std::regex_search(file.path,re)){
                    results.push_back(file);
                }
            }
            catch(...)
            {
                continue;
            }
            
        }
        else{
            if(fnmatch(pattern.c_str(),file.path.c_str(),0)==0){
                results.push_back(file);
            }
        }
    }

    return results;
}