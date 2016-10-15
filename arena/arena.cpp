#include "./arena.h"
#include <assert.h>

namespace leveldb{
    static const int kBlockSize = 4 * 1024;
    Arena::Arena()
    {
        alloc_ptr_ = NULL;
        alloc_bytes_remaining_ = 0;
    }
    Aerna::~Aerna(){
      for(size_t i = 0; i < block_.size(); i++)
      {
        delete[] block_[i];
      }
    }

    char* Arena::AllocateNewblock(size_t block_bytes)
    {
      char* result = new char[block_bytes];
      block_.push_back(result);
      return result;
    }

    char* Arena::AllocateFallback(size_t bytes)
    {
       if(bytes > kBlockSize/4){
         //当需要分配空间大于剩余内存并且大于1/4 kBlockSize时重新分配bytes大小的空间,
         //我感觉这样分配是为了减少内存分配次数
         char* result = AllocateNewblock(bytes);
         return result;
       }
       alloc_ptr_ = AllocateNewblock(kBlockSize);
       alloc_bytes_remaining_ = kBlockSize;

       char* result = alloc_ptr_;
       alloc_ptr_ += bytes;
       alloc_bytes_remaining_ -= bytes;
       return result;
    }

    //字节对齐内存分配
    char* Arena::AllocateAligned(size_t bytes){
      //用于判断运行环境的对齐大小
      const int align = (sizeof(void*) > 8) ? sizeof(void*) : 8;
      //内存对齐肯定是2的幂，此处用于判断是否是2的幂
      assert((align & (align -1)) == 0);

    }
}
