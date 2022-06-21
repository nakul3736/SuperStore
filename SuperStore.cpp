/*
Name:- Nakul Patel
ID:- 201901043
DAIICT  
*/


#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#define size 50
using namespace std;
struct inv_node
{
    long item_id;
    string name;
    float rate;
    int quantity;
    struct inv_node *next;
};
struct cus_node
{
    long cusid;
    string name;
    float points;
    struct cus_node *next;
};
struct bill_node
{
    long productid;
    int quantity,transaction_id;
    float price;
    string name;
    struct bill_node *next;
};
struct inv_node *inv_chain[size]={NULL};
struct cus_node *cus_chain[size]={NULL};
struct bill_node *bill_chain[size]={NULL};

class inventory
{
    public:
    void add_item(long id,string nam,float price,int quanti)
    {
        struct inv_node *newNode= new inv_node;
        newNode->item_id=id;
        newNode->name=nam;
        newNode->rate=price;
        newNode->quantity=quanti;
        newNode->next=NULL;
        int key=id%size;
        if(inv_chain[key]==NULL)
            inv_chain[key]=newNode;
        else
        {
            struct inv_node *temp=inv_chain[key];
            while(temp->next)
            {
                temp=temp->next;
            }
            temp->next=newNode;
        }
    }
    void delete_item(long id)
    {
        
        int key;
            key = id%size;
            inv_node *tmp ;
            tmp = inv_chain[key];

            if(tmp->item_id == id && tmp->next == NULL)
            {
                inv_chain[key] = NULL;
            }
            if(tmp->item_id == id && tmp->next != NULL)
            {
                tmp->item_id = tmp->next->item_id;
                tmp->name = tmp->next->name;
                tmp->rate = tmp->next->rate;
                tmp->quantity = tmp->next->quantity;

                inv_node *p;
                p = tmp->next;

                tmp->next = p->next;
                delete p;
            }
            else if(tmp->item_id != id)
            {
                while(tmp->next != NULL && tmp->next->item_id != id )
                {
                    tmp = tmp->next;
                }
                if(tmp->next != NULL && tmp->next->item_id == id)
                {
                    inv_node *p ;
                    p = tmp->next;
                    tmp->next = p->next;
                    delete p;
                }
                else
                {
                    cout<<"\n PRODUCT DOESN'T EXISTS"<<endl;
                }
            }
    }
    
    void product_info(long id)
    {
        int key = id % size;int flag=0;
    struct inv_node *temp = inv_chain[key];
    while(temp)
    {
        if(temp->item_id == id)
         {
             cout<<"product-name = "<<temp->name<<endl<<"Rate = "<<temp->rate<<endl<<"Quantity = "<<temp->quantity<<endl<<endl;
             flag=1;
         }   
        temp = temp->next;
    }
    if(flag==0)
    cout<<"No such product exist"<<endl;
    }
    
    void update_stock(long id,float price,int quanti)
    {
        int key=id%size;int flag=0;
        struct inv_node *temp=inv_chain[key];
        while(temp)
        {
            if(temp->item_id==id)
            {
            	flag=1;
                temp->rate=price;
                temp->quantity=quanti;
            }
            else
            temp=temp->next;
        }
        if(flag==0)
        cout<<"No suct product exist"<<endl;
    }
    void update_stock(long id,float price)
    {
        int key=id%size;int flag=0;
        struct inv_node *temp=inv_chain[key];
        while(temp)
        {
            if(temp->item_id==id)
            {
            	flag=1;
                temp->rate=price;
            }
            else 
            temp=temp->next;
        }
        if(flag==0)
        cout<<"No such product exist"<<endl;
    }
    void update_stock(long id,int quanti,int net)
    {
        int key=id%size;int flag=0;
        struct inv_node *temp=inv_chain[key];
        while(temp)
        {
            if(temp->item_id==id)
            {
            	flag=1;
                if(net==1)
                temp->quantity=quanti+temp->quantity;
                if(net==0)
                temp->quantity=temp->quantity-quanti;
            }
            else
            temp=temp->next;
        }
        if(flag==0)
        cout<<"Nos such product exist"<<endl;
    }
    int search(long id)
    {
    int key = id % size;
    struct inv_node *temp =inv_chain[key];
    while(temp)
    {
        if(temp->item_id == id)
            return 1;
        temp = temp->next;
    }
    return 0;
    }

};
class Manager :public inventory
{
    
};
class customer
{
    public:
    void add_customer(long id,string nam,float point)
    {
        struct cus_node *newNode=new cus_node;
        newNode->cusid=id;
        newNode->name=nam;
        newNode->points=point;
        newNode->next=NULL;
        int key=id%size;
        if(cus_chain[key]==NULL)
            cus_chain[key]=newNode;
        else
        {
            struct cus_node *temp=cus_chain[key];
            while(temp->next)
            {
                temp=temp->next;
            }
            temp->next=newNode;
        }
    }
    
    void detail(long id)
    {
        int key=id%size;int flag=0;
        struct cus_node *temp=cus_chain[key];
        while(temp)
        {
            if(temp->cusid == id)
            {
                cout<<"///";
                flag = 1;
                cout<<"\nCUSTOMER ID :- "<<temp->cusid<<"\nCUSTOMER NAME :- "<<temp->name<<"\nPOINTS :- "<<temp->points<<endl;;
                break;
            }
            else
            {
                temp=temp->next;
            }
        }
        if(flag == 0)
        {
            cout<<"NOT EXISTS"<<endl;
        }
    }
};
class Billing:public inventory
{
    public:
    void buy_from_prodID(long id)
    {
        int key,flag = 0,n;
        key = id%size;
        bill_node *p = new bill_node;
        inv_node *q;
        q = inv_chain[key];

        while(q)
        {
            if(q->item_id == id)
            {
                flag = 1;
                if(bill_chain[key] == NULL)
                {
                    p->productid= id;
                    p->price = q->rate;
                    p->name = q->name;
                    p->next = NULL;
                    cout<<"\nENTER HOW MANY QUANTITY YOU WANT TO BUY :- ";
                    cin>>n;
                    if(n <= q->quantity)
                    {
                        p->quantity = n;
                    }
                    else
                    {
                        cout<<"\nSORRY WE DON'T HAVE MUCH STOCK\n\nWE HAVE "<<q->quantity<<" QUANTITYS"<<endl;
                    }
                    bill_chain[key] = p;
                }
                 else
                {
                    bill_node *tmp;
                    tmp = bill_chain[key];
                    p->productid = id;
                    p->price = q->rate;
                    p->name = q->name;
                    p->next = NULL;

                    while(tmp->next != NULL)
                    {
                        tmp = tmp->next;
                    }

                    tmp->next = p;

                    cout<<"\nENTER HOW MANY QUANTITY YOU WANT TO BUY :- ";
                    cin>>n;
                    if(n <= q->quantity)
                    {
                        p->quantity = n;
                    }
                    else
                    {
                        cout<<"\nSORRY WE DON'T HAVE MUCH STOCK\n\nWE HAVE "<<q->quantity<<" QUANTITYS"<<endl;
                    }

                }
            }
            q = q->next;
        }
        if(flag == 0)
        {
            cout<<"\nPRODUCT DOESN'T EXITS  "<<endl;
        }
    }
    
    void update_product(long id) 
    {
        int key,choice,n,flag=0;
        key = id%size;
        bill_node *p;
        p = bill_chain[key];
        cout<<"\n1.CANCEL PRODUCT\n2.CHANGE QUANTITY"<<endl;
        cin>>choice;
        switch(choice)
        {
            case 1:
                    if(p->productid == id && p->next == NULL)
                    {
                        p = NULL;
                        flag=1;
                    }
                    else if(p->productid == id && p->next != NULL)
                    {
                        p->productid = p->next->productid;
                        p->name = p->next->name;
                        p->quantity = p->next->quantity;
                        p->price = p->next->price;
                        flag=1;
                        bill_node *tmp;
                        tmp = p->next;
                        p->next = tmp->next;
                        delete tmp;
                    }
                    else
                    {
                        while(p)
                        {
                            if(p->next->productid == id)
                            {
                                flag=1;
                                bill_node *tmp;
                                tmp = p->next;
                                p->next = tmp->next;
                                delete tmp;
                                break;
                            }
                            else
                            {
                                p = p->next;
                            }
                        }
                    }
                    if(flag==0)
                    cout<<"No such item you have buy"<<endl;
                break;
            case 2:
                cout<<"\nENTER HOW MANY QUANTITY YOU WANT TO CANCEL - ";
                cin>>n;
                if(p->productid == id)
                {
                        if(n < p->quantity)
                        {
                            p->quantity = p->quantity-n;
                            flag=1;
                        }
                        else if(n > p->quantity)
                        {
                            cout<<"\nSORRY\nYOUR PRODUCT QUATITY - "<<p->quantity;
                            flag=1;
                        }
                        else
                        {
                            if(p->next == NULL)
                            {
                                p = NULL;
                                flag=1;
                            }
                            else
                            {
                                p->productid = p->next->productid;
                                p->name = p->next->name;
                                p->quantity = p->next->quantity;
                                p->price = p->next->price;
                                flag=1;
                                bill_node *tmp;
                                tmp = p->next;
                                p->next = tmp->next;
                                delete tmp;
                            }
                        }
                }
                else
                {
                    while(p->next)
                    {
                        if(p->next->productid == id)
                        {
                            if(n > p->next->quantity)
                            {
                                cout<<"\nSORRY\nYOUR PRODUCT QUATITY - "<<p->next->quantity<<endl;
                                flag=1;
                                break;
                            }
                            else if(p->next->quantity > n)
                            {
                                p->next->quantity = p->next->quantity - n;
                                flag=1;
                                break;
                            }
                            else
                            {
                                bill_node *q;
                                q = p->next;
                                p->next = q->next;
                                flag=1;
                                delete q;
                                break;
                            }
                         }
                         else
                         {
                             p = p->next;
                         }
                     }
                 }
                 if(flag==0)
                 cout<<"No such product you have buy"<<endl;
                 break;
            default:
                cout<<"\nINVALID CHOICE"<<endl;
            }
    }
    
     void make_payment()
    {
        int i,key,flag = 0;
        static int tr_id = 1;
        long id;
        string na;
        float total = 0;
        bill_node *p = new bill_node;
        inv_node *check;


        cout<<"\nCUSTOMER ID - ";
        cin>>id;
        cout<<"\nCUSTOMER NAME :- ";
        cin.ignore();
        getline(cin,na);
        //cin>>na;
        cout<<"\nTRANSECTION ID - "<<tr_id++;
        p->transaction_id = tr_id;

        cout<<"\nPRODUCT ID\tPRODUCT-NAME\tRATE\tQUANTITY\tTOTAL";
        for(i=0;i<size;i++)
        {
            p = bill_chain[i];
            check = inv_chain[i];
            while(p)
            {
                cout<<"\n"<<p->productid<<"\t"<<p->name<<"\t\t"<<p->price<<"\t"<<p->quantity<<"\t\t"<<p->quantity*p->price;
                total = total + p->quantity*p->price;

                while(check)
                {
                    if(p->productid == check->item_id)
                    {
                        check->quantity = check->quantity - p->quantity;
                    }
                    check = check->next;
                }

                p = p->next;
            }
        }

        cout<<"\n--------------------------------------------------------------";
        cout<<"\n\t\t\t\t\t  TOTAL AMOUNT = "<<total<<"\n\n"<<endl;

        cus_node *q;
        cus_node *tmp;
        cus_node *temp = new cus_node;
        key = id%size;
        q = cus_chain[key];
        tmp = cus_chain[key];
        temp->name = na;
        temp->next = NULL;
        temp->cusid = id;

        while(q)
        {
            if(q->cusid == id && q->next == NULL)
            {
                flag = 1;
                q->points = q->points + total;
                temp->points = q->points;
                cus_chain[key] = temp;
                break;
            }
           else if(q->cusid == id)
            {
                flag = 1;
                q->points = q->points + total;
                temp->points = q->points;
                q = temp;
                break;
            }
            else
            {
                tmp = q;
                q = q->next;
            }
        }
        if(flag == 0)
        {
            temp->points = total;

            if(tmp == NULL)
            {
                cus_chain[key] = temp;
            }
            else
            {
                tmp->next = temp;
            }
        }
        else
        {
            delete tmp;
        }

        for(i=0;i<10;i++)
        {
            bill_chain[i] = NULL;
        }

}
};
int main() {
    int choice;
    Manager M;
    Billing B;
    customer C;
    long INVENTORY_DATASET[100][4] = { {111100000001,1,100,20},{111100000002,2,110,20}, {111100000003,3,120,20},{111100000004,4,130,20}, {111100000005,5,140,20},{111100000006,6,150,20}, {111100000007,7,160,20},{111100000008,8,170,20}, {111100000009,9,180,20},{111100000010,10,190,20}, {111100000011,11,200,20},{111100000012,12,210,20}, {111100000013,13,220,20},{111100000014,14,230,20}, {111100000015,15,240,20},{111100000016,16,250,20}, {111100000017,17,260,20},{111100000018,18,270,20}, {111100000019,19,280,20},{111100000020,20,290,20}, {111100000021,21,300,20},{111100000022,22,310,20}, {111100000023,23,320,20},{111100000024,24,330,20}, {111100000025,25,340,20},{111100000026,26,350,20}, {111100000027,27,360,20},{111100000028,28,370,20}, {111100000029,29,380,20},{111100000030,30,390,20}, {111100000031,31,400,20},{111100000032,32,410,20}, {111100000033,33,420,20},{111100000034,34,430,20}, {111100000035,35,440,20},{111100000036,36,450,20}, {111100000037,37,460,20},{111100000038,38,470,20}, {111100000039,39,480,20},{111100000040,40,490,20}, {111100000041,41,500,20},{111100000042,42,510,20}, {111100000043,43,520,20},{111100000044,44,530,20}, {111100000045,45,540,20},{111100000046,46,550,20}, {111100000047,47,560,20},{111100000048,48,570,20}, {111100000049,49,580,20},{222200001111,50,590,20}, {222200001114,51,600,20},{222200001117,52,610,20}, {222200001120,53,620,20},{222200001123,54,630,20}, {222200001126,55,640,20},{222200001129,56,650,20}, {222200001132,57,660,20},{222200001135,58,670,20}, {222200001138,59,680,20},{222200001141,60,690,20}, {222200001144,61,700,20},{222200001147,62,710,20}, {222200001150,63,720,20},{222200001153,64,730,20}, {222200001156,65,740,20},{222200001159,66,750,20}, {222200001162,67,760,20},{222200001165,68,770,20}, {222200001168,69,780,20},{222200001171,70,790,20}, {222200001174,71,800,20},{222200001177,72,810,20}, {222200001180,73,820,20},{222200001183,74,830,20}, {222200001186,75,840,20},{222200001189,76,850,20}, {222200001192,77,860,20},{222200001195,78,870,20}, {222200001198,79,880,20},{222200001201,80,890,20}, {222200001204,81,900,20},{222200001207,82,910,20}, {222200001210,83,920,20},{222200001213,84,930,20}, {222200001216,85,940,20},{222200001219,86,950,20}, {222200001222,87,960,20},{222200001225,88,970,20}, {222200001228,89,980,20},{222200001231,90,990,20}, {222200001234,91,1000,20},{222200001237,92,1010,20},{222200001240,93,1020,20},{222200001243,94,1030,20}, {222200001246,95,1040,20},{222200001249,96,1050,20}, {222200001252,97,1060,20},{222200001255,98,1070,20}, {222200001258,99,1080,20},{222200001261,100,1090,20}};
    long CUSTOMER_DATASET[100][3] = { {9400000001,1,0},{9400000002,2,0},{9400000003,3,0},{9400000004,4,0}, {9400000005,5,0},{9400000006,6,0},{9400000007,7,0},{9400000008,8,0}, {9400000009,9,0},{9400000010,10,0}, {9400000011,11,0},{9400000012,12,0},{9400000013,13,0}, {9400000014,14,0},{9400000015,15,0},{9400000016,16,0}, {9400000017,17,0},{9400000018,18,0},{9400000019,19,0}, {9400000020,20,0}, {9400000021,21,0},{9400000022,22,0},{9400000023,23,0}, {9400000024,24,0},{9400000025,25,0},{9400000026,26,0}, {9400000027,27,0},{9400000028,28,0},{9400000029,29,0}, {9400000030,30,0}, {9400000031,31,0},{9400000032,32,0},{9400000033,33,0}, {9400000034,34,0},{9400000035,35,0},{9400000036,36,0}, {9400000037,37,0},{9400000038,38,0},{9400000039,39,0}, {9400000040,40,0}, {9400000041,41,0},{9400000042,42,0},{9400000043,43,0}, {9400000044,44,0},{9400000045,45,0},{9400000046,46,0}, {9400000047,47,0},{9400000048,48,0},{9400000049,49,0}, {9400000050,50,0}, {9400000051,51,0},{9400000052,52,0},{9400000053,53,0}, {9400000054,54,0},{9400000055,55,0},{9400000056,56,0}, {9400000057,57,0},{9400000058,58,0},{9400000059,59,0}, {9400000060,60,0}, {9400000061,61,0},{9400000062,62,0},{9400000063,63,0}, {9400000064,64,0},{9400000065,65,0},{9400000066,66,0}, {9400000067,67,0},{9400000068,68,0},{9400000069,69,0}, {9400000070,70,0}, {9400000071,71,0},{9400000072,72,0},{9400000073,73,0}, {9400000074,74,0},{9400000075,75,0},{9400000076,76,0}, {9400000077,77,0},{9400000078,78,0},{9400000079,79,0}, {9400000080,80,0}, {9400000081,81,0},{9400000082,82,0},{9400000083,83,0}, {9400000084,84,0},{9400000085,85,0},{9400000086,86,0}, {9400000087,87,0},{9400000088,88,0},{9400000089,89,0}, {9400000090,90,0}, {9400000091,91,0},{9400000092,92,0},{9400000093,93,0}, {9400000094,94,0},{9400000095,95,0},{9400000096,96,0}, {9400000097,97,0},{9400000098,98,0},{9400000099,99,0}, {9400000100,100,0}};
    
    for(int i=0;i<100;i++)
    {
        M.add_item(INVENTORY_DATASET[i][0],to_string(INVENTORY_DATASET[i][1]),INVENTORY_DATASET[i][2],INVENTORY_DATASET[i][3]);
    }
    for(int i=0;i<100;i++)
    {
        C.add_customer(CUSTOMER_DATASET[i][0],to_string(CUSTOMER_DATASET[i][1]),CUSTOMER_DATASET[i][2]);
    }
    while(1)
    {
    cout<<"---------------SUPER MARKET--------------"<<endl;
    cout<<"1.MANAGER"<<endl<<"2.CUSTOMER"<<endl<<"3.BILLING"<<endl<<"4.EXIT"<<endl;
    cin>>choice;
    switch(choice)
    {
        int manager_choice;
        case 1:
        do{
        long pro_Id;string name;int quantity,amount;float price;
        cout<<"Enter 1 to add new item to inventory"<<endl<<"Enter 2 to remove any item from inventory"<<endl<<"Enter 3 to change the price of any product"<<endl<<"Enter 4 to change quantity of any product"<<endl<<"Enter 5 to change both price and quantity of product"<<endl<<"Enter 6 to go get product info"<<endl<<"Enter 7 to go to super market menu"<<endl;
        
        cin>>manager_choice;
        switch(manager_choice)
        {
            case 1:
            cout<<"\nEnter product id = ";cin>>pro_Id;cout<<"\nEnter product name = ";cin.ignore(); getline(cin,name);cout<<"\nEnter price of Product";cin>>price;cout<<"\nEnter quantity of Product you want";cin>>quantity;cout<<endl;
            M.add_item(pro_Id,name,price,quantity);
            break;
            case 2:
            cout<<"Enter the product Id you want to remove from inventory";
            cin>>pro_Id;cout<<endl;
            M.delete_item(pro_Id);
            break;
            case 3:
            cout<<"\nEnter the id of the product whose price you want to change";cin>>pro_Id;
            cout<<"\nEnter the new price of product";cin>>price;cout<<endl;
            M.update_stock(pro_Id,price);
            break;
            case 4:
            cout<<"\nEnter the id of the product whose quantity you want to change";cin>>pro_Id;
            cout<<"\nEnter 1 if you want to increase the stock or Enter 0 if you want to decrease it";cin>>amount;cout<<endl;
            if(amount==1)
            {
                cout<<"\nEnter the  quantity of atock that you want to increase";cin>>quantity;
                M.update_stock(pro_Id,quantity,amount);
            }
            else if(amount==0)
            {
                cout<<"\nEnter the  quantity of atock that you want to decrease";cin>>quantity;
                M.update_stock(pro_Id,quantity,amount);
            }
            else
            cout<<"\nEnter the valid number"<<endl;
            
            break;
            case 5:
               cout<<"\nEnter the id of the product whose quantity and price you want to change - ";cin>>pro_Id;
               cout<<"\nEnter the new price of product - ";cin>>price;
                cout<<"\nEnter 1 if you want to increase the stock or Enter 0 if you want to decrease it - ";cin>>amount;
            if(amount==1)
            {
                cout<<"\nEnter the  quantity of atock that you want to increase - ";cin>>quantity;
                M.update_stock(pro_Id,quantity,amount);
            }
            else if(amount==0)
            {
                cout<<"\nEnter the  quantity of atock that you want to decrease - ";cin>>quantity;
                M.update_stock(pro_Id,quantity,amount);
            }
            else
            cout<<"\nEnter the valid number"<<endl;cout<<endl;
            break;
            case 6:
            cout<<"Enter product id - ";cin>>pro_Id;cout<<endl;
            M.product_info(pro_Id);
            break;
            default:
            cout<<"Invalid choice\n"<<endl;
        }
        }while(manager_choice!=7);
        break;
        case 2:
            int cus_choice;
            do
            {
                long cus_id;string name;
                cout<<"Enter 1 to add customer"<<endl;cout<<"Enter 2 for customer detail"<<endl;cout<<"Enter 3 to go to super market menu"<<endl;
                cin>>cus_choice;
                switch(cus_choice)
                {
                    case 1:
                    cout<<"Enter customer id -";cin>>cus_id;cout<<endl<<"Enter customer name -";cin.ignore();getline(cin,name);cout<<endl;
                    C.add_customer(cus_id,name,0);
                    break;
                    case 2:
                    cout<<"\nEnter customer id whose info you want - ";
                    cin>>cus_id;
                    C.detail(cus_id);
                    break;
                    case 3:
                    
                    break;
                    default:
                    cout<<"\nInvalid choice"<<endl;
                }
            }while(cus_choice!=3);
        break;
        case 3:
         int bill_menu;
         do
         {
             long bill_id;
             cout<<"\n1.BUY PRODUCT\n2.UPDATE PRODUCT THAT  YOU BUY\n3.MAKE PAYMENT\n4.Exit"<<endl;
             cin>>bill_menu;
             switch(bill_menu)
             {
                 case 1:
                 cout<<"Enter product id -";cin>>bill_id;cout<<endl;
                 B.buy_from_prodID(bill_id);
                 break;
                 case 2:
                 cout<<"\nENTER PRODUCT ID - ";cin>>bill_id;cout<<endl;
                 B.update_product(bill_id);
                 break;
                 case 3:
                 B.make_payment();
                 break;
                 case 4:
                 break;
             }
         }while(bill_menu!=4);
        break;
        case 4:
           return 0;
        default:
        cout<<"\nInvalid choice"<<endl;
    }
    }
}





