#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>
// ���
#include "conio.h"

// ����ѧ������
struct stuInfo
{
    int Id;                         // id ��Ϊ0
    char name[20 + 1];              //'\0'
    int attendance_times;           // ���ڴ���
    int normal_score;
    int exam_score;
    int IsFinishTestExercises;      // [0,1]
    int Exercises_score;
};
// <@Q>:1.����ṹ���ж�� 2.�ṹ���������ʲô 3.����� stuInfoд�� }���ʾʲô

typedef struct stuInfo STUINFO_t;
// <@Q>:typedef 1.��ʾʲô��˼ 2.��仰���������


// ���ݴ�ӡ�� stdout
void StuInfoPrint2(STUINFO_t* s)
{
    printf("ѧ��:%8d            ", s->Id);
    printf("����:%s\n", s->name);
    printf("���ڴ���:%-4d        ", s->attendance_times);
    printf("ƽʱ�ɼ�:%-4d\n", s->normal_score);
    printf("���Գɼ�:%-4d        ", s->exam_score);
    printf("    �۲�:\n");
    printf("�Ƿ���ɸ�����:%-4s  ", s->IsFinishTestExercises ? "��" : "��");
    if (s->IsFinishTestExercises)
        printf("�������:%d", s->Exercises_score);
    printf("\n----------------------------\n");
}

// ʹ�ýṹ�������ѧ����Ϣ  [���Զ���ɽṹ��洢]
///////////////////////////////////////////////////////////////
#define STUINFOARRAY_MAX    100         // �������100��ѧ����Ϣ
STUINFO_t at_stu[STUINFOARRAY_MAX];     // ���ٵ�����
STUINFO_t* ptra_stu = at_stu;           // ָ�������ָ��
int stuNum = 0;                         // ѧ������
STUINFO_t* ptra_stuEnd = &at_stu[0];    // �������ָ��
///////////////////////////////////////////////////////////////

// ��ȡstuinfo�����׵�ַ
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

// ����һ�����ݽ�����ַ
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

// 1 ��û�ҵ��� �����ʲô
int StuFindByName(char* name, STUINFO_t** p)
{
    // �������
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
                res = 1;    // �ҵ���
                break;
            }
        }
        p_cur++;
    }
    *p = p_cur;
    return res;
}

// 1 ��û�ҵ��� �����ʲô
int StuFindById(int id, STUINFO_t** p)
{
    // �������
    int res = 0;
    STUINFO_t* p_cur = GetStuArrayAddr();
    STUINFO_t* p_end = GetStuArrayAddrEnd();
    while (p_cur != p_end)
    {
        int cur_id = p_cur->Id;
        if (cur_id == id)
        {
            res = 1;    // �ҵ���
            break;
        }
        p_cur++;
    }
    *p = p_cur;
    return res;
}

// �ṹ�忽��
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

// �����Ϣϵͳ
int StuStructAdd(const STUINFO_t* p_data)
{
    STUINFO_t* p_cur = GetStuArrayAddr();
    STUINFO_t* p_end = GetStuArrayAddrEnd();
    //STUINFO_t *p_end = GetStuArrayAddrEnd();
    int cnt = GetStuNum();
    if (cnt > STUINFOARRAY_MAX)
        return 1;   // ����
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

// ɾ��
int StuStructDel(const STUINFO_t* p_data)
{
    STUINFO_t* p_cur = GetStuArrayAddr();
    STUINFO_t* p_end = GetStuArrayAddrEnd();
    int res = 1;
    int cnt = GetStuNum();
    if (cnt == 0)
        return 1;   // û��������
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
// ��ʾ
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

///////////////////////////////////////�������///////////////////////////////////////

// ��������ָ�뺯�� // ���� ����  ������ָ�
STUINFO_t* StuPtr_swap(STUINFO_t** a, STUINFO_t** b)
{
    STUINFO_t* tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
    return *a;
}
// ����
int StuSelec_sortByScore(STUINFO_t** ia_data, int len)
{
    // ѡ������,��ʣ�����ҵ���С��Ԫ�أ��ŵ�һ�������λ��
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
// ����
int StuSelec_sortByID(STUINFO_t** ia_data, int len)
{
    // ѡ������,��ʣ�����ҵ���С��Ԫ�أ��ŵ�һ�������λ��
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

///////////////////////////////////////�ļ�ϵͳ///////////////////////////////////////
// �������ݵ� buf
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
// �� buf��������
void ImportStuInfo_Str(STUINFO_t* s, const char* buf)
{
    // printf("ƥ�䵽����:%s", &buf[7]);
        // %*[^,] ������һ��,������ [data],
        // %[^,] �˴� name �� ,����
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

// �ļ���д
int TestReport(int op)
{
    FILE* w_file = NULL;
    time_t curtim;
    int tmp;
    w_file = fopen("stuOut.csv", "a+");     //����׷��ģʽ
    if (w_file == NULL)
    {
        printf("�ļ�����ʧ��,��������Ƿ�ر�!\n");
        return 1;
    }
    if (op == 0)
    {
        time(&curtim);
        fprintf(w_file, "[time]:%s", asctime(gmtime(&curtim)));
        fprintf(w_file, "[type]:ID  ,Name,����,ƽʱ,����,�Ƿ��и�����,�������\n");
    }
    else {
        fprintf(w_file, "����һ����ԵĻ�!\n");
    }
    // ���딵��
    char buf[128];  // ���л���buf
    STUINFO_t* p_cur = GetStuArrayAddr();
    STUINFO_t* p_end = GetStuArrayAddrEnd();
    int i = 0;
    while (p_cur != p_end)
    {
        if (p_cur->Id != 0)
        {
            memset(buf, 0, 128);
            ExportStuInfo_Str(p_cur, buf);
            fprintf(w_file, "[data],%s\n", buf); // ��ʽ����
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
        printf("�ļ���ȡʧ��,�����ļ��Ƿ�ر�!\n");
        return 1;
    }
    // ��ʽ����ȡ����
    char buf[256];
    while (!feof(w_file))
    {
        STUINFO_t tmp;
        int flag = 0;
        fgets(buf, 256, w_file);
        printf("s:%s", buf);
        if (memcmp(buf, "[data]", 6))  // �����
            continue;
        printf("ƥ�䵽����:%s", &buf[7]);
        // %*[^,] ������һ��,������ [data],
        // %[^,] �˴� name �� ,����
        // sscanf(&buf[7], "%d,%[^,],%d,%d,%d,%d,%d",
        // sscanf(&buf[0], "%*[^,],%d,%[^,],%d,%d,%d,%d,%d",
        ImportStuInfo_Str(&tmp, (const char*)&buf[7]);
        //StuStructCpy(p,&tmp);       // �������ⲿ
        STUINFO_t* p_tmp;
        if (StuFindById(tmp.Id, &p_tmp))
        {
            //��������
            StuStructCpy(p_tmp, &tmp);       // �������ⲿ
        }
        else {
            // �������
            StuStructAdd(&tmp);          // ������ϵͳ
        }
        p++;
        if (!--size)
            break;
    }
    fclose(w_file);
    return 0;
}
///////////////////////////////////////OP�ӿ�///////////////////////////////////////
// ��� ѧ����Ŀ
//int StuFindById(int id, STUINFO_t **p)
// ����һ������  STUINFO_t *tmp;  STUINFO_t **p ����ϵ��ʲô���Լ��ڷֱ���ʲôʱ�����仯��




void OP_StuInfo_Add(STUINFO_t* p_data)
{
    STUINFO_t* tmp;
    if (StuFindById(p_data->Id, &tmp))
    {
        // �ҵ��͸���
        StuStructCpy(tmp, p_data);
        printf("����ѧ����Ϣ�ɹ�");
    }
    else
    {
        if (!StuStructAdd(p_data))
            printf("���ѧ����Ϣ�ɹ�\n");
        else
            printf("���ѧ����Ϣʧ��\n");
    }
}
// ɾ�� ��ѧ��
void OP_StuInfo_DelById(int id)
{
    STUINFO_t* p_data;
    if (StuFindById(id, &p_data))
    {
        StuStructDel(p_data);
        printf("�ɹ��h��idΪ %d ��ѧ����Ϣ\n", id);
    }
    else {
        printf("δ�ҵ�����Ϊ %d ��ѧ����Ϣ\n", id);
    }
}
// ɾ�� ������
void OP_StuInfo_DelByName(char* name)
{
    STUINFO_t* p_data;
    if (StuFindByName(name, &p_data))
    {
        StuStructDel(p_data);
        printf("�ɹ��h������Ϊ %s ��ѧ����Ϣ\n", name);
    }
    else {
        printf("δ�ҵ�����Ϊ %s ��ѧ����Ϣ", name);
    }
}
///////////////////////////////////////UI�ӿ�///////////////////////////////////////
// ��� ѧ����Ŀ
void UI_StuInfo_Add()
{
    STUINFO_t tmp;
    STUINFO_t* p = &tmp;
    printf("ʹ��scanf�����Ϣ,�����ʽ�����½���\n");
    printf("ID,Name,����,ƽʱ,����,�Ƿ��и�����(0,1),�������\n");
    // %[^,] ����,�����name �Ľ���
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
// ɾ�� ��ѧ��
void UI_StuInfo_DelById()
{
    //STUINFO_t* p;   // ��һ��ָ���������
    int id = 0;
    printf("����Ҫɾ��ѧ����id:");
    scanf("%d", &id);
    // OP_StuInfo_DelById(id,p);
    OP_StuInfo_DelById(id);
}
// ɾ�� ������
void UI_StuInfo_DelByName()
{
    // STUINFO_t* p ;// ��һ��ָ���������
    char name[21];
    printf("����Ҫɾ��ѧ��������:");
    scanf("%s", name);
    OP_StuInfo_DelByName(name);
}
// ���� 0:��ѧ�� 1:���ɼ�
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
    // ����ѡ������
    if (mode == 0)
    {
        printf("��ID����:\n");
        StuSelec_sortByID(p, cnt);
    }
    else if (mode == 1)
    {
        printf("���ɼ�����:\n");
        StuSelec_sortByScore(p, cnt);
    }
    else {
        printf("��ԭʼ˳�����:\n");
    }
    for (int i = 0; i < cnt; i++)
    {
        printf("\n------------[%d]------------\n", i + 1);
        StuInfoPrint2(p[i]);
    }
    free(p);    // ɾ������Ŀռ�
}
///////////////////////////////////////// ������ҵ /////////////////////////////////////////
// ��дOP��UI ���ִ���
// ������main �ĵ���

///////////////////////////////////////// �κ���ҵ /////////////////////////////////////////
// �Ķ� UI_CMD_test ���ܵ�ʵ��
extern void UI_CMD_test();

//int StuFindById(int id, STUINFO_t **p)
// ����һ������  STUINFO_t *tmp;  STUINFO_t **p ����ϵ��ʲô���Լ��ڷֱ���ʲôʱ�����仯��

// [����]�����������������ͼ
//[����ǩ��]
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


    // ��ʼ�� ѧ����Ϣ��
    const STUINFO_t sutcfg[] = {
        {20210401,"��1",4,75,85,0,10},
        {20210402,"��2",4,75,85,1,10},
        {20210403,"��3",4,75,85,0,10},
        {20210404,"��4",4,75,85,1,10},
        {20210405,"��5",4,75,85,0,10},
        {20210406,"��6",4,75,85,0,10},
    };
    // ����ӵ�ѧ����Ϣ��2
    const STUINFO_t sutcfg2[] = {
        {20210411,"��1",4,75,85,0,10},
        {20210412,"��2",4,75,85,0,10},
        {20210413,"��3",4,75,85,1,10},
        {20210414,"��4",4,75,85,0,10},
        {20210415,"��5",4,75,85,1,10},
        {20210416,"��6",4,75,85,0,10},
    };
    //////////////////////UI����//////////////////////
    UI_CMD_test();
    //////////////////////��ӵ�ϵͳ//////////////////////
    // 1. ����ʼ��ѧ����Ϣϵͳ�� <@Q:>sizeof(sutcfg) / sizeof(sutcfg[0]) ��ʾʲô��˼
    for (int i = 0; i < sizeof(sutcfg) / sizeof(sutcfg[0]); i++)
        StuStructAdd(&sutcfg[i]);
    // 2.��ʾ��Ӻ������ѧ����Ϣ
    StuListShow();
    //////////////////////OP����//////////////////////

    // ����ɾ��ѧ��Ϊ 20210404 ��ѧ����Ϣ, ����ʾ
    //OP_StuInfo_DelById(20210404);
    //StuListShow();
    // ����ɾ��ѧ�Ų���ϵͳ�е�ѧ����Ϣ ����ʾ
    /*OP_StuInfo_DelById(20210400);
    StuListShow();*/
    // ����ɾ������Ϊ "��5"��ѧ����Ϣ ����ʾ
   /* OP_StuInfo_DelByName("��5");
    StuListShow();*/
    // �����Ϣ��2������ ����ʾ
    //for (int i = 0; i < sizeof(sutcfg2) / sizeof(sutcfg2[0]); i++)
    //    StuStructAdd(&sutcfg2[i]);
    //StuListShow();
    // ִ�����򣬲���������Ľ��
    //UI_StuListSort(0);
    //UI_CMD_test UI����



    return 1;
}

void UI_CMD_test()
{
    char cmd;
    do {
        printf("\n����[1~7]ѡ��ͬ��UI����,[N,n�˳�]\n");
        printf("0:��ʾ����ѧ����Ϣ\n");
        printf("1:��� ѧ����Ϣ\n");
        printf("2:ɾ�� ͨ������\n");
        printf("3:ɾ�� ͨ��ID\n");
        printf("4:���� ��ѧ��\n");
        printf("5:���� ���ɼ�\n");
        printf("6:[����]����ѧ����Ϣ(�� stu.csv)\n");
        printf("7:[����]����ѧ����Ϣ(�� stuOut.csv)\n");
        ///printf("8:[����]����ѧ����Ϣ(�� stuOut.csv)\n");
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

// �޸�ѧ����Ϣ  ����ͨ�� ɾ�� + ���ʵ��
void UI_SetStuInfo()
{
    STUINFO_t* p;   // ��һ��ָ���������
    int id = 0;
    printf("����Ҫ����ѧ����ѧ��:");
    scanf("%d", &id);
    if (StuFindById(id, &p))
    {
        printf("ID,Name,����,ƽʱ,����,�Ƿ��и�����(0,1),�������\n");
        // %[^,] ����,�����name �Ľ���
        scanf("%d,%[^,],%d,%d,%d,%d,%d",
            &p->Id,
            p->name,
            &p->attendance_times,
            &p->normal_score,
            &p->exam_score,
            &p->IsFinishTestExercises,
            &p->Exercises_score);
        printf("�ɹ��޸�ѧ��Ϊ %d ��ѧ����Ϣ\n", id);
    }
    else {
        printf("δ�ҵ�ѧ��Ϊ %d ��ѧ����Ϣ", id);
    }
}
