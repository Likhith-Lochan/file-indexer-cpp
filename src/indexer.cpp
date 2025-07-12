#include "indexer.hpp"
#include <iostream>

namespace fs=boost::filesystem;

FileIndexer::FileIndexer(const std::string &root,int thread_count) : root_path(root),num_threads(thread_count),done(false){
    directory_queue.push_back(fs::path(root));
}

void FileIndexer::start(){
    
    for(int i=0;i<num_threads;i++){
        threads.push_back(std::thread(&FileIndexer::worker,this));
    }

    for(size_t i=0;i<threads.size();++i){
        if(threads[i].joinable()) threads[i].join();
    }

    done=true;
}

void FileIndexer::worker(){
    while(true){
        fs::path current_dir;

        {
            std::lock_guard<std::mutex> lock(queue_mutex);
            if(directory_queue.empty()){
                break;
            }
            current_dir=directory_queue.back();
            directory_queue.pop_back();

        }

        scanDirectory(current_dir);
    }
}

void FileIndexer::scanDirectory(const fs::path& dir){
    try
    {
        fs::directory_iterator end_itr;

        for(fs::directory_iterator it(dir);it!=end_itr;++it){

            try
            {
                if(fs::is_directory(it->path())){
                   std::lock_guard<std::mutex> lock(queue_mutex);
                   directory_queue.push_back(it->path()); 
                }
                else if(fs::is_regular_file(it->path())){
                    FileEntry file;
                    file.path = it->path().string();
                    file.size=fs::file_size(it->path());
                    file.last_modified=fs::last_write_time(it->path());
                    
                    std::lock_guard<std::mutex> lock(result_mutex);
                    indexed_files.push_back(file);
                }
            }
            catch(...)
            {
                //skip file on error
            }
            
        }
    }
    catch(const std::exception& e)
    {
        std::cerr <<"Error scanning "<<dir<<":" <<e.what() << '\n';
    }
    
}