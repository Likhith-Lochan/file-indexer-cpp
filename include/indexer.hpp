#ifndef __INDEXER_HPP__
#define __INDEXER_HPP__

#include <string>
#include <vector>
#include <boost/filesystem.hpp>
#include <mutex>
#include <regex>
#include <thread>
#include <ctime>

struct FileEntry {
    std::string path;
    uintmax_t size;
    std::time_t last_modified;
};


class FileIndexer {
    public:
     FileIndexer(const std::string &root,int thread_count =4);
     void start();
     std::vector<FileEntry>  search(const std::string& pattern,bool use_regex=false);

    private:
     void worker();
     void scanDirectory(const boost::filesystem::path& dir);

     std::string root_path;
     int num_threads;
     std::vector<std::thread> threads;

     std::mutex queue_mutex;
     std::mutex result_mutex;
     std::vector<boost::filesystem::path> directory_queue;
     std::vector<FileEntry> indexed_files;
     bool done;     

};


#endif // __INDEXER_HPP__