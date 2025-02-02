#include<iostream>
#include<filesystem>
#include<vector>
#include<thread>
#include<queue>
#include"threadpool"

#define GREEN "\033[32m"
#define BLUE "\033[34m"
#define YELLOW "\033[93m"
#define END "\033[0m"
using namespace std;
using namespace filesystem;

threadpool pool(24);

struct SearchConfig {
    std::string root_path;    // 要搜索的根目录
    std::string file_type;    // 要搜索的文件类型，如 ".txt"、".cpp" 等
    int max_concurrency;      // 最大并发数
    int max_depth;            // 最大搜索深度
    bool skip_hidden;         // 是否跳过隐藏文件或目录
    std::vector<std::string> skip_paths;   // 要跳过的目录或文件的路径
};

int recur_count = 0;
queue<path>dirQueue;

void search(SearchConfig &config) {
    try
    {
        for(auto entry : directory_iterator(config.root_path)) {
            string filename = entry.path().filename();
            string filepath = entry.path();
            if(entry.is_symlink()) {
                continue;
            }
            if(config.skip_hidden && filename[0] == '.') {
                continue;
            }
            int size_tail = config.file_type.size();
            if(!entry.is_directory() && filename.find(config.file_type) != string::npos && filename.find(config.file_type) + size_tail == filename.size()) {
                cout<<YELLOW<<filename<<END<<":  "<<BLUE<<filepath<<END<<endl;
            }
            if(entry.is_directory()) {
                dirQueue.push(filepath); 
            }
        }
    } catch(const std::filesystem::filesystem_error& e) {
        // std::cerr << "Error: No such file within max_depth" << std::endl;
    }
    if(recur_count >= config.max_depth) {
        return;
    }
    if(dirQueue.empty()) {
        return;
    }
    config.root_path = dirQueue.front();
    dirQueue.pop();
    recur_count ++;
    pool.submit([&config](){
        search(config);
    });
    recur_count --;
}

int main()
{
    SearchConfig config;
    config.root_path = "/";
    config.file_type = ".md";
    config.max_depth = 10000000;
    config.skip_hidden = true;
     
    search(config);
    pool.stop(); // 一定要记得结束哦

    return 0;
}