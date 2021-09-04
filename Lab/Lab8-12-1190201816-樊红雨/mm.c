/*
 * mm-naive.c - The fastest, least memory-efficient malloc package.
 * 
 * In this naive approach, a block is allocated by simply incrementing
 * the brk pointer.  A block is pure payload. There are no headers or
 * footers.  Blocks are never coalesced or reused. Realloc is
 * implemented directly using mm_malloc and mm_free.
 *
 * NOTE TO STUDENTS: Replace this header comment with your own header
 * comment that gives a high level description of your solution.
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

#include "mm.h"
#include "memlib.h"

/*********************************************************
 * NOTE TO STUDENTS: Before you do anything else, please
 * provide your team information in the following struct.
 ********************************************************/
team_t team = {
    /* Team name */
    "FHY-1190201816",
    /* First member's full name */
    "Fan Hong Yu",
    /* First member's email address */
    "1159592260@qq.com",
    /* Second member's full name (leave blank if none) */
    "",
    /* Second member's email address (leave blank if none) */
    ""
};

/* single word (4) or double word (8) alignment */
#define ALIGNMENT 8
#define MAX_LEN 16
#define WSIZE 4
#define DSIZE 8
#define INITCHUNKSIZE (1 << 4)
#define CHUNKSIZE (1 << 4)

/* rounds up to the nearest multiple of ALIGNMENT */
#define ALIGN(size) (((size) + (ALIGNMENT-1)) & ~0x7)

#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MIN(x, y) ((x) < (y) ? (x) : (y))

#define PACK(size, alloc) ((size) | (alloc))

/* Read and write a word at address p */
#define GET(p) (*(size_t *)(p))
#define PUT(p, val) (*(size_t *)(p) = (val))

/* Read the size and allocated fields from address p */
#define GET_SIZE(p) (GET(p) & ~0x7)
#define GET_ALLOC(p) (GET(p) & 0x1)

/* Given block ptr ptr, compute address of its header and footer */
#define HDRP(ptr) ((char *)(ptr)-WSIZE)
#define FTRP(ptr) ((char *)(ptr) + GET_SIZE(HDRP(ptr)) - DSIZE)

/* Given block ptr ptr, compute address of next and previous blocks */
#define NEXT_BLKP(ptr) ((char *)(ptr) + GET_SIZE(((char *)(ptr)-WSIZE)))
#define PREV_BLKP(ptr) ((char *)(ptr)-GET_SIZE(((char *)(ptr)-DSIZE)))

#define SET_PTR(p, ptr) (*(unsigned int *)(p) = (unsigned int)(ptr))

#define PRED_PTR(ptr) ((char *)(ptr))
#define SUCC_PTR(ptr) ((char *)(ptr) + WSIZE)

#define PRED(ptr) (*(char **)(ptr))
#define SUCC(ptr) (*(char **)(SUCC_PTR(ptr)))


#define SIZE_T_SIZE (ALIGN(sizeof(size_t)))

void *List[MAX_LEN];
static char *heap_listp;

static void *extend_heap(size_t size);
static void *coalesce(void *bp);
static void *place(void *bp, size_t size);
static void printblock(void *bp);
static void checkblock(void *bp);
static void InsertNode(void *bp, size_t size); //插入到空闲链表
static void DeleteNode(void *bp); //删除

/* 
 * mm_init - initialize the malloc package.
 */
int mm_init(void)
{
    int i;
    for (i = 0 ; i <MAX_LEN ; i++)
    {
        List[i] = NULL;
    }
    heap_listp = mem_sbrk(4 * WSIZE);
    if (heap_listp == NULL)
    {
        return -1;
    }

    PUT(heap_listp,0);
    PUT(heap_listp + (1 * WSIZE), PACK(DSIZE, 1)); //序言块
    PUT(heap_listp + (2 * WSIZE), PACK(DSIZE, 1));
    PUT(heap_listp + (3 * WSIZE), PACK(0, 1)); //结尾块

    if (extend_heap(INITCHUNKSIZE) == NULL)
    {
        return -1;
    }
    return 0;
}

/* 
 * mm_malloc - Allocate a block by incrementing the brk pointer.
 *     Always allocate a block whose size is a multiple of the alignment.
 */
void *mm_malloc(size_t size)
{
    char *ptr = NULL;
    int i = 0;
    if (size == 0) return NULL;
    if (size <= DSIZE) 
        size = 2 * DSIZE; 
    else 
        size = ALIGN(size + DSIZE); //内存对齐
    size_t asize = size;
    while (i < MAX_LEN)
    {
        //先找合适的空闲链表
        if (((asize <= 1) && (List[i] != NULL)))
        {
            ptr = List[i];
            //找到链表，在该链寻找大小合适的未分配块
            while ((ptr != NULL) && ((size > GET_SIZE(HDRP(ptr)))))
                ptr = PRED(ptr);

            //找到对应的未分配的块
            if (ptr != NULL)
                break;
        }
        asize >>= 1;
        i++;
    }
    /* 没有找到合适的未分配块，则扩展堆 */
    if (ptr == NULL) if ((ptr = extend_heap(MAX(size, CHUNKSIZE))) == NULL) return NULL;
    /* 在未分配块中allocate size大小的块 */
    ptr = place(ptr, size);
    return ptr;
}

//扩展堆
static void *extend_heap(size_t size)
{
    char *ptr;
    size = ALIGN(size);
    if ((ptr = mem_sbrk(size)) == (void *)-1)
        return NULL;
    PUT(HDRP(ptr), PACK(size, 0));
    PUT(FTRP(ptr), PACK(size, 0));
    PUT(HDRP(NEXT_BLKP(ptr)), PACK(0, 1));
    //插入到分离空闲表中
    InsertNode(ptr, size);
    
    return coalesce(ptr);
}


/*将大小字节的块放在空闲块bp的开始处，并且如果余数至少是最小块大小则拆分*/
static void *place(void *bp, size_t asize)
{
    size_t csize = GET_SIZE(HDRP(bp));
    size_t remaining = csize - asize; /* allocate size大小的空间后剩余的大小 */
    DeleteNode(bp);
    /* 如果剩余的大小小于最小块，则不分离原块 */
    if (remaining < DSIZE * 2)
    {
        PUT(HDRP(bp), PACK(csize, 1));
        PUT(FTRP(bp), PACK(csize, 1));
    }
    else if (asize >= 96)
    {
        PUT(HDRP(bp), PACK(remaining, 0));
        PUT(FTRP(bp), PACK(remaining, 0));
        PUT(HDRP(NEXT_BLKP(bp)), PACK(asize, 1));
        PUT(FTRP(NEXT_BLKP(bp)), PACK(asize, 1));
        InsertNode(bp, remaining);
        return NEXT_BLKP(bp);
    }

    else
    {
        PUT(HDRP(bp), PACK(asize, 1));
        PUT(FTRP(bp), PACK(asize, 1));
        PUT(HDRP(NEXT_BLKP(bp)), PACK(remaining, 0));
        PUT(FTRP(NEXT_BLKP(bp)), PACK(remaining, 0));
        InsertNode(NEXT_BLKP(bp), remaining);
    }
    return bp;
}


//插入到空闲链表
static void InsertNode(void *ptr, size_t size)
{
    int i = 0;
    void *search = NULL;
    void *insert = NULL;
    while ((i < MAX_LEN - 1) && (size > 1)) // 根据size的大小找到对应的分离空闲链表
    {
        size >>= 1;
        i++;
    }
    //找到分离空闲链表，在该链中寻找对应的插入位置，并且保持链中块由小到大分布
    search = List[i];
    while ((search != NULL) && (size > GET_SIZE(HDRP(search))))
    {
        insert = search;
        search = PRED(search);
    }
    
    if (search != NULL)
    {
        /* 1.在开头插入*/
        if (insert == NULL)
        {
            SET_PTR(PRED_PTR(ptr), search);
            SET_PTR(SUCC_PTR(search), ptr);
            SET_PTR(SUCC_PTR(ptr), NULL);
            List[i] = ptr;
        }
        /* 2. 在中间插入*/
        else
        {
            SET_PTR(PRED_PTR(ptr), search);
            SET_PTR(SUCC_PTR(search), ptr);
            SET_PTR(SUCC_PTR(ptr), insert);
            SET_PTR(PRED_PTR(insert), ptr);
        }
    }
    else
    {
        /*3.第一次插入*/
        if (insert == NULL)
        { 
            SET_PTR(PRED_PTR(ptr), NULL);
            SET_PTR(SUCC_PTR(ptr), NULL);
            List[i] = ptr;
        }
        /*4.在结尾插入 */
        else
        { 
            SET_PTR(PRED_PTR(ptr), NULL);
            SET_PTR(SUCC_PTR(ptr), insert);
            SET_PTR(PRED_PTR(insert), ptr);
        }
    }
}

//从空闲链表中删除
static void DeleteNode(void *ptr)
{
    int i = 0;
    size_t size = GET_SIZE(HDRP(ptr));
    //根据size的大小找到对应的分离空闲链表
    while ((i < MAX_LEN - 1) && (size > 1))
    {
        size >>= 1;
        i++;
    }
    //四种可能性
    if (PRED(ptr) != NULL)
    {
        //表头删除，中间有块
        if (SUCC(ptr) == NULL)
        {
            SET_PTR(SUCC_PTR(PRED(ptr)), NULL);
            List[i] = PRED(ptr);
        }
        //中间删除
        else
        {
            SET_PTR(SUCC_PTR(PRED(ptr)), SUCC(ptr));
            SET_PTR(PRED_PTR(SUCC(ptr)), PRED(ptr));
        }
    }
    else
    {
        //3. 结尾删除
        if (SUCC(ptr) != NULL) SET_PTR(PRED_PTR(SUCC(ptr)), NULL);
        //4. 第一次删除
        else List[i] = NULL;
    }
}

//合并块
static void *coalesce(void *ptr)
{
    size_t prev = GET_ALLOC(HDRP(PREV_BLKP(ptr)));
    size_t next = GET_ALLOC(HDRP(NEXT_BLKP(ptr)));
    size_t size = GET_SIZE(HDRP(ptr));
    if (prev && next) return ptr;//case1
    else if (prev && !next) //case2
    {
        DeleteNode(ptr);
        DeleteNode(NEXT_BLKP(ptr));
        size += GET_SIZE(HDRP(NEXT_BLKP(ptr)));
        PUT(HDRP(ptr), PACK(size, 0));
        PUT(FTRP(ptr), PACK(size, 0));
    }
    else if (!prev && next) //case3
    {
        DeleteNode(ptr);
        DeleteNode(PREV_BLKP(ptr));
        size += GET_SIZE(HDRP(PREV_BLKP(ptr)));
        PUT(FTRP(ptr), PACK(size, 0));
        PUT(HDRP(PREV_BLKP(ptr)), PACK(size, 0));
        ptr = PREV_BLKP(ptr);
    }
    else //case4
    {
        DeleteNode(ptr);
        DeleteNode(PREV_BLKP(ptr));
        DeleteNode(NEXT_BLKP(ptr));
        size += GET_SIZE(HDRP(PREV_BLKP(ptr))) + GET_SIZE(HDRP(NEXT_BLKP(ptr)));
        PUT(HDRP(PREV_BLKP(ptr)), PACK(size, 0));
        PUT(FTRP(NEXT_BLKP(ptr)), PACK(size, 0));
        ptr = PREV_BLKP(ptr);
    }
    //合并后的free块插入到空闲链接表中
    InsertNode(ptr, size);
    return ptr;
}

/*
 * mm_free - Freeing a block does nothing.
 */
void mm_free(void *ptr)
{
    size_t size = GET_SIZE(HDRP(ptr));

    PUT(HDRP(ptr), PACK(size, 0));
    PUT(FTRP(ptr), PACK(size, 0));
    InsertNode(ptr, size);
    coalesce(ptr);
}

/*
 * mm_realloc - Implemented simply in terms of mm_malloc and mm_free
 */
void *mm_realloc(void *ptr, size_t size)
{
    void *newptr = ptr;
    int remaining;
    
    if (size == 0) return NULL;

    if (size <= DSIZE) 
        size = 2 * DSIZE; 
    else 
        size = ALIGN(size + DSIZE); //内存对齐
    /* 如果size小于原来块的大小，直接返回原来的块 */
    if ((remaining = GET_SIZE(HDRP(ptr)) - size) >= 0) return ptr;
    /* 否则先检查地址连续下一个块是否为未分配块或者该块是堆的结束块 */
    else if (!GET_ALLOC(HDRP(NEXT_BLKP(ptr))) || !GET_SIZE(HDRP(NEXT_BLKP(ptr))))
    {
        /* 如果加上后面连续地址上的未分配块空间也不够，那么需要扩展块 */
        if ((remaining = GET_SIZE(HDRP(ptr)) + GET_SIZE(HDRP(NEXT_BLKP(ptr))) - size) < 0)
        {
            if (extend_heap(MAX(-remaining, CHUNKSIZE)) == NULL) return NULL;
            remaining += MAX(-remaining, CHUNKSIZE);
        }
        /* 从分离空闲链表中删除刚刚利用的未分配块并设置新块的头尾 */
        DeleteNode(NEXT_BLKP(ptr));
        PUT(HDRP(ptr), PACK(size + remaining, 1));
        PUT(FTRP(ptr), PACK(size + remaining, 1));
    }
    /* 如果没有可以利用的连续未分配块，只能申请新的不连续的未分配块 */
    else
    {
        newptr = mm_malloc(size);
        memcpy(newptr, ptr, GET_SIZE(HDRP(ptr)));
        mm_free(ptr);
    }
    return newptr;
}

//检查堆的一致性
void mm_checkheap(int verbose)
{
    char *bp = heap_listp;

    if (verbose) printf("Heap (%p):\n", heap_listp);
    if ((GET_SIZE(HDRP(heap_listp)) != DSIZE) || !GET_ALLOC(HDRP(heap_listp))) printf("Bad prologue header\n");
    checkblock(heap_listp);
    for (bp = heap_listp; GET_SIZE(HDRP(bp)) > 0; bp = NEXT_BLKP(bp))
    {
        if (verbose)printblock(bp);
        checkblock(bp);
    }
    if (verbose) printblock(bp);
    if ((GET_SIZE(HDRP(bp)) != 0) || !(GET_ALLOC(HDRP(bp)))) printf("Bad epilogue header\n");
}

static void printblock(void *bp)
{
    size_t hsize, halloc, fsize, falloc;
    hsize = GET_SIZE(HDRP(bp));
    halloc = GET_ALLOC(HDRP(bp));
    fsize = GET_SIZE(FTRP(bp));
    falloc = GET_ALLOC(FTRP(bp));
    if (hsize == 0)
    {
        printf("%p: EOL\n", bp);
        return;
    }
    printf("%p: header: [%d:%c] footer: [%d:%c]\n", bp, hsize, (halloc ? 'a' : 'f'), fsize, (falloc ? 'a' : 'f'));
}

static void checkblock(void *bp)
{
    if ((size_t)bp % 8) printf("Error: %p is not doubleword aligned\n", bp);
    if (GET(HDRP(bp)) != GET(FTRP(bp))) printf("Error: header does not match footer\n");
}












