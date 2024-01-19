#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>
// 添加
#include "conio.h"

// 定义学生数据
struct stuInfo
{
    int Id;                         // id 不为0
    char name[20 + 1];              //'\0'
    int attendance_times;           // 考勤次数
    int normal_score;
    int exam_score;
    int IsFinishTestExercises;      // [0,1]
    int Exercises_score;
};
// <@Q>:1.这个结构体有多大 2.结构体的名称是什么 3.如果把 stuInfo写在 }后表示什么

typedef struct stuInfo STUINFO_t;
// <@Q>:typedef 1.表示什么意思 2.这句话你能理解吗


// 数据打印到 stdout
void StuInfoPrint2(STUINFO_t* s)
{
    printf("学号:%8d            ", s->Id);
    printf("姓名:%s\n", s->name);
    printf("考勤次数:%-4d        ", s->attendance_times);
    printf("平时成绩:%-4d\n", s->normal_score);
    printf("考试成绩:%-4d        ", s->exam_score);
    printf("    综测:\n");
    printf("是否完成附加题:%-4s  ", s->IsFinishTestExercises ? "是" : "否");
    if (s->IsFinishTestExercises)
        printf("附加题分:%d", s->Exercises_score);
    printf("\n----------------------------\n");
}

// 使用结构体数组存学生信息  [可以定义成结构体存储]
///////////////////////////////////////////////////////////////
#define STUINFOARRAY_MAX    100         // 最多容纳100个学生信息
STUINFO_t at_stu[STUINFOARRAY_MAX];     // 开辟的数组
STUINFO_t* ptra_stu = at_stu;           // 指向数组的指针
int stuNum = 0;                         // 学生数量
STUINFO_t* ptra_stuEnd = &at_stu[0];    // 数组结束指针
///////////////////////////////////////////////////////////////

// 获取stuinfo数据首地址
STUINFO_t* GetStuArrayAddr()
{
    return &at_stu[0];
}

STUINFO_t* GetStuArrayAddrEnd()
{
    return ptra_stuEnd;
}

void SetStuArrayAddrEnd(STUINFO_t* p)
{
    ptra_stuEnd = p;
}

int GetStuNum()
{
    return stuNum;
}
void SetStuNum(int s)
{
    stuNum = s;
}

int StuNumInc()
{
    stuNum++;
    return stuNum;
}
int StuNumDec()
{
    stuNum--;
    return stuNum;
}

// 更新一次数据结束地址
void UpdataStu()
{
    STUINFO_t* p = GetStuArrayAddr();
    int cnt = STUINFOARRAY_MAX;
    while (cnt--)
    {
        if (0 != (p + cnt)->Id)
        {
            break;
        }
    }
    SetStuArrayAddrEnd(p + cnt + 1);
}

// 1 找没找到， 结果是什么
int StuFindByName(char* name, STUINFO_t** p)
{
    // 数组查找
    int res = 0;
    STUINFO_t* p_cur = GetStuArrayAddr();
    STUINFO_t* p_end = GetStuArrayAddrEnd();

    while (p_cur != p_end)
    {
        if (p_cur->Id != 0)
        {
            char* cur_name = p_cur->name;
            if (0 == strcmp(cur_name, name))
            {
                res = 1;    // 找到啦
                break;
            }
        }
        p_cur++;
    }
    *p = p_cur;
    return res;
}

// 1 找没找到， 结果是什么
int StuFindById(int id, STUINFO_t** p)
{
    // 数组查找
    int res = 0;
    STUINFO_t* p_cur = GetStuArrayAddr();
    STUINFO_t* p_end = GetStuArrayAddrEnd();
    while (p_cur != p_end)
    {
        int cur_id = p_cur->Id;
        if (cur_id == id)
        {
            res = 1;    // 找到啦
            break;
        }
        p_cur++;
    }
    *p = p_cur;
    return res;
}

// 结构体拷贝
void StuStructCpy(STUINFO_t* dst, const STUINFO_t* src)
{
    dst->Id = src->Id;
    dst->attendance_times = src->attendance_times;
    dst->normal_score = src->normal_score;
    dst->exam_score = src->exam_score;
    dst->IsFinishTestExercises = src->IsFinishTestExercises;
    dst->Exercises_score = src->Exercises_score;
    strcpy(dst->name, (const char*)src->name);
}

// 添加信息系统
int StuStructAdd(const STUINFO_t* p_data)
{
    STUINFO_t* p_cur = GetStuArrayAddr();
    STUINFO_t* p_end = GetStuArrayAddrEnd();
    //STUINFO_t *p_end = GetStuArrayAddrEnd();
    int cnt = GetStuNum();
    if (cnt > STUINFOARRAY_MAX)
        return 1;   // 错误
    while (p_cur->Id != 0)
    {
        p_cur++;
    }
    StuStructCpy(p_cur, p_data);
    StuNumInc();
    if (p_cur + 1 > p_end)
    {
        SetStuArrayAddrEnd(p_cur + 1);
    }
    return 0;
}

// 删除
int StuStructDel(const STUINFO_t* p_data)
{
    STUINFO_t* p_cur = GetStuArrayAddr();
    STUINFO_t* p_end = GetStuArrayAddrEnd();
    int res = 1;
    int cnt = GetStuNum();
    if (cnt == 0)
        return 1;   // 没有数据了
    while (p_cur != p_end)
    {
        if (p_cur->Id == p_data->Id)
        {
            p_cur->Id = 0;
            res = 0;
            StuNumDec();
            // UpdataStu();
            break;
        }
        p_cur++;
    }
    return res;
}
// 显示
void StuListShow()
{
    STUINFO_t* p_cur = GetStuArrayAddr();
    STUINFO_t* p_end = GetStuArrayAddrEnd();
    while (p_cur != p_end)
    {
        if (p_cur->Id != 0)
        {
            StuInfoPrint2(p_cur);
        }
        p_cur++;
    }
    printf("===========[All Num=%d]===========\n", GetStuNum());
}

///////////////////////////////////////排序测试///////////////////////////////////////

// 交换两个指针函数 // 排序 保存  對應的指針
STUINFO_t* StuPtr_swap(STUINFO_t** a, STUINFO_t** b)
{
    STUINFO_t* tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
    return *a;
}
// 排序
int StuSelec_sortByScore(STUINFO_t** ia_data, int len)
{
    // 选择排序,从剩余中找到最小的元素，放第一个排序的位置
    int minIndex;
    for (int i = 0; i < len - 1; i++)
    {
        minIndex = i;
        for (int j = i + 1; j < len; j++)
        {
            if (ia_data[j]->exam_score < ia_data[minIndex]->exam_score)
            {
                minIndex = j;
            }
        }
        StuPtr_swap(&ia_data[minIndex], &ia_data[i]);
    }
    return 0;
}
// 排序
int StuSelec_sortByID(STUINFO_t** ia_data, int len)
{
    // 选择排序,从剩余中找到最小的元素，放第一个排序的位置
    int minIndex;
    for (int i = 0; i < len - 1; i++)
    {
        minIndex = i;
        for (int j = i + 1; j < len; j++)
        {
            if (ia_data[j]->Id < ia_data[minIndex]->Id)
            {
                minIndex = j;
            }
        }
        StuPtr_swap(&ia_data[minIndex], &ia_data[i]);
    }
    return 0;
}

///////////////////////////////////////文件系统///////////////////////////////////////
// 导出数据到 buf
void ExportStuInfo_Str(STUINFO_t* s, char* buf)
{
    int len = 0;
    len += sprintf(&buf[len], "%d,", s->Id);
    len += sprintf(&buf[len], "%s,", s->name);
    len += sprintf(&buf[len], "%d,", s->attendance_times);
    len += sprintf(&buf[len], "%d,", s->normal_score);
    len += sprintf(&buf[len], "%d,", s->exam_score);
    len += sprintf(&buf[len], "%d,", s->IsFinishTestExercises);
    len += sprintf(&buf[len], "%d,", s->Exercises_score);
}
// 从 buf导入数据
void ImportStuInfo_Str(STUINFO_t* s, const char* buf)
{
    // printf("匹配到数据:%s", &buf[7]);
        // %*[^,] 调过第一个,的内容 [data],
        // %[^,] 此处 name 用 ,结束
    scanf(buf, "%d,%[^,],%d,%d,%d,%d,%d",
        // sscanf(&buf[0], "%*[^,],%d,%[^,],%d,%d,%d,%d,%d",
        &s->Id,
        s->name,
        &s->attendance_times,
        &s->normal_score,
        &s->exam_score,
        &s->IsFinishTestExercises,
        &s->Exercises_score);
}

// 文件读写
int TestReport(int op)
{
    FILE* w_file = NULL;
    time_t curtim;
    int tmp;
    w_file = fopen("stuOut.csv", "a+");     //采用追加模式
    if (w_file == NULL)
    {
        printf("文件创建失败,请检查程序是否关闭!\n");
        return 1;
    }
    if (op == 0)
    {
        time(&curtim);
        fprintf(w_file, "[time]:%s", asctime(gmtime(&curtim)));
        fprintf(w_file, "[type]:ID  ,Name,考勤,平时,考试,是否有附加题,附加题分\n");
    }
    else {
        fprintf(w_file, "这是一句测试的话!\n");
    }
    // 寫入數據
    char buf[128];  // 单行缓冲buf
    STUINFO_t* p_cur = GetStuArrayAddr();
    STUINFO_t* p_end = GetStuArrayAddrEnd();
    int i = 0;
    while (p_cur != p_end)
    {
        if (p_cur->Id != 0)
        {
            memset(buf, 0, 128);
            ExportStuInfo_Str(p_cur, buf);
            fprintf(w_file, "[data],%s\n", buf); // 格式控制
        }
        p_cur++;
    }
    fclose(w_file);
    return 0;
}
int TestImport(STUINFO_t* p, int size)
{
    FILE* w_file = NULL;
    w_file = fopen("stu.csv", "r");
    if (w_file == NULL)
    {
        printf("文件读取失败,请检查文件是否关闭!\n");
        return 1;
    }
    // 格式化读取数据
    char buf[256];
    while (!feof(w_file))
    {
        STUINFO_t tmp;
        int flag = 0;
        fgets(buf, 256, w_file);
        printf("s:%s", buf);
        if (memcmp(buf, "[data]", 6))  // 不相等
            continue;
        printf("匹配到数据:%s", &buf[7]);
        // %*[^,] 调过第一个,的内容 [data],
        // %[^,] 此处 name 用 ,结束
        // sscanf(&buf[7], "%d,%[^,],%d,%d,%d,%d,%d",
        // sscanf(&buf[0], "%*[^,],%d,%[^,],%d,%d,%d,%d,%d",
        ImportStuInfo_Str(&tmp, (const char*)&buf[7]);
        //StuStructCpy(p,&tmp);       // 导出到外部
        STUINFO_t* p_tmp;
        if (StuFindById(tmp.Id, &p_tmp))
        {
            //更新数据
            StuStructCpy(p_tmp, &tmp);       // 导出到外部
        }
        else {
            // 添加数据
            StuStructAdd(&tmp);          // 导出到系统
        }
        p++;
        if (!--size)
            break;
    }
    fclose(w_file);
    return 0;
}
///////////////////////////////////////OP接口///////////////////////////////////////
// 添加 学生条目
//int StuFindById(int id, STUINFO_t **p)
// 补充一个问题  STUINFO_t *tmp;  STUINFO_t **p 的联系是什么，以及在分别在什么时候发生变化，




void OP_StuInfo_Add(STUINFO_t* p_data)
{
    STUINFO_t* tmp;
    if (StuFindById(p_data->Id, &tmp))
    {
        // 找到就更新
        StuStructCpy(tmp, p_data);
        printf("更新学生信息成功");
    }
    else
    {
        if (!StuStructAdd(p_data))
            printf("添加学生信息成功\n");
        else
            printf("添加学生信息失败\n");
    }
}
// 删除 按学号
void OP_StuInfo_DelById(int id)
{
    STUINFO_t* p_data;
    if (StuFindById(id, &p_data))
    {
        StuStructDel(p_data);
        printf("成功刪除id为 %d 的学生信息\n", id);
    }
    else {
        printf("未找到姓名为 %d 的学生信息\n", id);
    }
}
// 删除 按姓名
void OP_StuInfo_DelByName(char* name)
{
    STUINFO_t* p_data;
    if (StuFindByName(name, &p_data))
    {
        StuStructDel(p_data);
        printf("成功刪除姓名为 %s 的学生信息\n", name);
    }
    else {
        printf("未找到姓名为 %s 的学生信息", name);
    }
}
///////////////////////////////////////UI接口///////////////////////////////////////
// 添加 学生条目
void UI_StuInfo_Add()
{
    STUINFO_t tmp;
    STUINFO_t* p = &tmp;
    printf("使用scanf添加信息,输入格式按以下进行\n");
    printf("ID,Name,考勤,平时,考试,是否有附加题(0,1),附加题分\n");
    // %[^,] 遇到,会结束name 的接收
    scanf("%d,%[^,],%d,%d,%d,%d,%d",
        &p->Id,
        p->name,
        &p->attendance_times,
        &p->normal_score,
        &p->exam_score,
        &p->IsFinishTestExercises,
        &p->Exercises_score);
    OP_StuInfo_Add(p);
}
// 删除 按学号
void UI_StuInfo_DelById()
{
    //STUINFO_t* p;   // 传一个指针变量即可
    int id = 0;
    printf("输入要删除学生的id:");
    scanf("%d", &id);
    // OP_StuInfo_DelById(id,p);
    OP_StuInfo_DelById(id);
}
// 删除 按姓名
void UI_StuInfo_DelByName()
{
    // STUINFO_t* p ;// 传一个指针变量即可
    char name[21];
    printf("输入要删除学生的姓名:");
    scanf("%s", name);
    OP_StuInfo_DelByName(name);
}
// 排序 0:按学号 1:按成绩
void UI_StuListSort(int mode)
{
    int cnt = GetStuNum();
    STUINFO_t** p = (STUINFO_t**)malloc(sizeof(STUINFO_t*) * cnt);
    STUINFO_t* p_cur = GetStuArrayAddr();
    STUINFO_t* p_end = GetStuArrayAddrEnd();
    int i = 0;
    while (p_cur != p_end)
    {
        if (p_cur->Id != 0)
        {
            p[i++] = p_cur;
        }
        p_cur++;
    }
    // 采用选择排序
    if (mode == 0)
    {
        printf("按ID排序:\n");
        StuSelec_sortByID(p, cnt);
    }
    else if (mode == 1)
    {
        printf("按成绩排序:\n");
        StuSelec_sortByScore(p, cnt);
    }
    else {
        printf("按原始顺序输出:\n");
    }
    for (int i = 0; i < cnt; i++)
    {
        printf("\n------------[%d]------------\n", i + 1);
        StuInfoPrint2(p[i]);
    }
    free(p);    // 删除分配的空间
}
///////////////////////////////////////// 课堂作业 /////////////////////////////////////////
// 填写OP、UI 部分代码
// 补充完main 的调用

///////////////////////////////////////// 课后作业 /////////////////////////////////////////
// 阅读 UI_CMD_test 功能的实现
extern void UI_CMD_test();

//int StuFindById(int id, STUINFO_t **p)
// 补充一个问题  STUINFO_t *tmp;  STUINFO_t **p 的联系是什么，以及在分别在什么时候发生变化，

// [附加]梳理各函数调用流程图
//[关于签到]
typedef union {
    char a;
    short b;
    int c;
    unsigned int d;
    char aa[2];
    short bb[2];
}U_4Byte;
typedef struct {
    char a;
    short b;
    int c;
    unsigned int d;
    char aa[2];
    short bb[2];
}Tt_4Byte;
int main()
{
    Tt_4Byte tt_4[2];
    printf("%d %d\n", sizeof(Tt_4Byte), sizeof(tt_4[0]));
    U_4Byte t_4 = { 0 };
    t_4.a = 'a';
    printf("%d %d %d %u \n", t_4.a, t_4.b, t_4.c, t_4.d);
    t_4.b = 65535;
    t_4.c = 0x8FFF;
    t_4.d = 0xFFFF;
    t_4.aa[0] = 250;
    t_4.aa[1] = 'b';
    printf("%d %d %d %u \n", t_4.a, t_4.b, t_4.c, t_4.d);
    t_4.bb[0] = 10;
    t_4.bb[1] = 65535;
    printf("%d %d %d %u \n", t_4.a, t_4.b, t_4.c, t_4.d);


    // 初始化 学生信息表
    const STUINFO_t sutcfg[] = {
        {20210401,"李1",4,75,85,0,10},
        {20210402,"李2",4,75,85,1,10},
        {20210403,"李3",4,75,85,0,10},
        {20210404,"李4",4,75,85,1,10},
        {20210405,"李5",4,75,85,0,10},
        {20210406,"李6",4,75,85,0,10},
    };
    // 待添加的学生信息表2
    const STUINFO_t sutcfg2[] = {
        {20210411,"王1",4,75,85,0,10},
        {20210412,"王2",4,75,85,0,10},
        {20210413,"王3",4,75,85,1,10},
        {20210414,"王4",4,75,85,0,10},
        {20210415,"王5",4,75,85,1,10},
        {20210416,"王6",4,75,85,0,10},
    };
    //////////////////////UI测试//////////////////////
    UI_CMD_test();
    //////////////////////添加到系统//////////////////////
    // 1. 将初始化学生信息系统中 <@Q:>sizeof(sutcfg) / sizeof(sutcfg[0]) 表示什么意思
    for (int i = 0; i < sizeof(sutcfg) / sizeof(sutcfg[0]); i++)
        StuStructAdd(&sutcfg[i]);
    // 2.显示添加后的所有学生信息
    StuListShow();
    //////////////////////OP测试//////////////////////

    // 试着删除学号为 20210404 的学生信息, 并显示
    //OP_StuInfo_DelById(20210404);
    //StuListShow();
    // 试着删除学号不在系统中的学生信息 并显示
    /*OP_StuInfo_DelById(20210400);
    StuListShow();*/
    // 试着删除姓名为 "李5"的学生信息 并显示
   /* OP_StuInfo_DelByName("李5");
    StuListShow();*/
    // 添加信息表2的数据 并显示
    //for (int i = 0; i < sizeof(sutcfg2) / sizeof(sutcfg2[0]); i++)
    //    StuStructAdd(&sutcfg2[i]);
    //StuListShow();
    // 执行排序，并输出排序后的结果
    //UI_StuListSort(0);
    //UI_CMD_test UI测试



    return 1;
}

void UI_CMD_test()
{
    char cmd;
    do {
        printf("\n输入[1~7]选择不同的UI功能,[N,n退出]\n");
        printf("0:显示所有学生信息\n");
        printf("1:添加 学生信息\n");
        printf("2:删除 通过姓名\n");
        printf("3:删除 通过ID\n");
        printf("4:排序 按学号\n");
        printf("5:排序 按成绩\n");
        printf("6:[慎用]导入学生信息(从 stu.csv)\n");
        printf("7:[慎用]导出学生信息(到 stuOut.csv)\n");
        ///printf("8:[慎用]导出学生信息(到 stuOut.csv)\n");
        fflush(stdout);
        cmd = getchar();
        switch (cmd)
        {
        case '0':StuListShow(); break;
        case '1':UI_StuInfo_Add(); break;
        case '2':UI_StuInfo_DelByName(); break;
        case '3':UI_StuInfo_DelById(); break;
        case '4':UI_StuListSort(0); break;
        case '5':UI_StuListSort(1); break;
        case '6': {
            TestImport(GetStuArrayAddr(), STUINFOARRAY_MAX);
        }; break;
        case '7':TestReport(0); break;
        default:; break;
        }
        if (cmd == 'N' || cmd == 'n')
            break;
    } while (1);
}

// 修改学生信息  可以通过 删除 + 添加实现
void UI_SetStuInfo()
{
    STUINFO_t* p;   // 传一个指针变量即可
    int id = 0;
    printf("输入要更改学生的学号:");
    scanf("%d", &id);
    if (StuFindById(id, &p))
    {
        printf("ID,Name,考勤,平时,考试,是否有附加题(0,1),附加题分\n");
        // %[^,] 遇到,会结束name 的接收
        scanf("%d,%[^,],%d,%d,%d,%d,%d",
            &p->Id,
            p->name,
            &p->attendance_times,
            &p->normal_score,
            &p->exam_score,
            &p->IsFinishTestExercises,
            &p->Exercises_score);
        printf("成功修改学号为 %d 的学生信息\n", id);
    }
    else {
        printf("未找到学号为 %d 的学生信息", id);
    }
}
