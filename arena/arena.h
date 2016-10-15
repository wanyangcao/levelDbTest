#ifndef LEVELDB_ARENA_H
#define LEVELDB_ARENA_H

#include <vector>
#include <assert.h>
#include <stddef.h>
#include <stdint.h>

namespace{
    class Arena{
    public:
        Arena();
        ~Arena();

        //分配bytes大小的内存空间并返回指向该地址的指针
        char* Allocate(size_t bytes);
        //分配byte大小的空间，保证字节对其
        char* AllocateAligned(size_t bytes);
    private:
        //当前以内存快不足以所申请内存时调用此函数
        char* AllocateFallback(size_t bytes);
        char* AllocateNewblock(size_t block_bytes);
        //指向当前内存快神谕空间的地址
        char* alloc_ptr_;
        //当前内存快剩余量
        size_t alloc_bytes_remaining_;
        //当前新分配内存快的容器
        std::vector<char*> block_;
        //禁止copY
        Arena(const Arena&);
        void operator=(const Arena&);

    };


    inline Arena::Allocate(size_t bytes)
    {
      assert(bytes > 0);
      if(bytes < alloc_bytes_remaining_)
      {
        char* result = alloc_ptr_;
        alloc_ptr_ += bytes;
        alloc_bytes_remaining_ -= bytes;
        return result;

      }
      //如果分配内存大于剩余内存，重新分配
      return AllocateFallback(bytes);
    }
}

#endif
