//#include<fstream>
//#include<utility>
#include <bits/stdc++.h>

using namespace std;

void product_found_decorator(){
     cout<<"============================"<<endl;
     cout<<"=======PRODUCT FOUND========"<<endl;
     cout<<"============================"<<endl;
     cout<<endl;
     cout<<"SHOP DETAILS WHERE PRODUCT IS AVAILABLE :: "<<endl;

}

/// Product class will contain the product_name ,product price and product_count
///class product(data_members ) product_name ,price ,count
///class product member function set_product_details,make_product_details,return count,return name ,return price
class product{
private:
    string product_name;
    string price;
    string count;
public:
    void set_product_details(string name,string price ,string count){
        product_name= name;
        this->price = price;
        this->count = count ;
    }
    void make_product_details(){
        cout<<"Enter the product name : ";
        getline(cin,product_name,'\n');
        cout<<"Enter the product price : ";
        cin>>price ;
        cout<<"Enter the product count ";
        cin>>count;
    }
    string return_count(){
        return count;
    }
    string return_name(){
        return product_name;
    }
    string return_price(){
        return price;
    }
};

/// subcategory class contains subcategory name
/// array of objects of product
///constructor to set the distinct product =0
/// it also contains set_category_name,update_distinct_count,return_distinct_count
class subcategory: public product{
    private:
    string sub_name;
    public:
    product objects_pro[100];
    int distinct_product;
    subcategory(){
        distinct_product =0;
    }
    void set_subcategory_name(string subname){
        sub_name = subname;
    }
    void update_distinct_product(){
        this->distinct_product +=1;
    }
    void decrease_distinct_product(){
        this->distinct_product -=1;
    }
    int return_distinct_product(){
        return this->distinct_product;
    }
    string return_sub_name(){
        return this->sub_name;
    }
    void addProduct(string name,string cost,string count){
        this->distinct_product +=1;
        objects_pro[this->distinct_product-1].set_product_details(name,cost,count);
    }

};
class shop :public subcategory{
    protected:
    string shop_id;
    string name;
    string category;
    string shop_address;
    string password;
    int count_subcategory;

    public:
    subcategory obj_sub[10];
    shop(){
        int count_subcategory = 0;
    }
    string return_shop_category(){
        return this->category;
    }
    string return_id(){
        return shop_id;
    }
    void set_id(string id){
        this->shop_id = id;
    }
    void set_shopname(string name){
        this->name=  name;
    }
    void set_category(string category){
        this->category = category;
    }
    void set_shop_address(string shop_add){
        shop_address = shop_add;
    }
    void increment_sub_count(){
        this->count_subcategory+=1;
    }
    int return_sub_count(){
        return count_subcategory;
    }
    string return_shop_name(){
        return this->name;
    }
    string return_password(){
        return this->password;
    }
    string return_shopadd(){
				return shop_address;
    }

    void set_password(string pass){
        this->password = pass;
    }
    bool match_password(string pass){
        //bool result ;
        if(this->password!=pass){
            return false;
        }
        return true;
    }
    friend void seller(shop* shops,int count_of_shops);
    friend void customer(shop*shops,int count_of_shops);

};

void account(shop* shops,int count_of_shops){
        string id;
        string pass;
        cout<<"Enter UserID : ";
        fflush(stdin);
        getline(cin,id);
        cout<<"Enter Password : ";
        fflush(stdin);
        getline(cin,pass);
        int index =-1;
        for(int i=0;i<count_of_shops;i++){
            if(shops[i].return_id()==id){
                index = i;
                break;
            }
        }
        if(index==-1){
            cout<<"UserID not found\n";
            return;
        }
        bool dec = shops[index].match_password(pass);
        cout<<dec<<endl;
        if(dec==false){
            cout<<"ACCESS DENIED!!!!"<<endl;
        }

        if(dec){
            int decision;

            while(decision!=3){
                cout<<"1.TO ADD A PRODUCT "<<endl;
                cout<<"2.TO DELETE A PRODUCT "<<endl;
                cout<<"3.LOGOUT"<<endl;
                cout<<"Enter your choice : ";
                cin>>decision;
                fflush(stdin);
                if(decision==1){
                    cout<<"Enter the subcategory under which you want to add product : ";
                    string sub ;
                    getline(cin,sub);

                    cout<<"Enter the product name : ";
                    string pro_name;
                    getline(cin,pro_name);
                    cout<<"Enter the price of this product : ";
                    string pro_price;
                    getline(cin,pro_price);
                    cout<<"Enter the count of this product : ";
                    string pro_count;
                    getline(cin,pro_count);
                    int shop_index= index;
                    int subcategory_index =-1;
                    for(int l = 0;l<shops[shop_index].return_sub_count();l++){
                                if(sub==shops[shop_index].obj_sub[l].return_name()){
                                    subcategory_index = l;
                                    break;
                                }
                    }
                    if(subcategory_index==-1){
                        cout<<"Subcatrgory Not Present "<<endl;
                        cout<<"Creating new Subcategory......"<<endl;
                        shops[shop_index].increment_sub_count();
                        shops[shop_index].obj_sub[shops[shop_index].return_sub_count()-1].set_subcategory_name(sub);
                        shops[shop_index].obj_sub[shops[shop_index].return_sub_count()-1].addProduct(pro_name,pro_price,pro_count);
                    }
                    else{
                        shops[shop_index].obj_sub[shops[shop_index].return_sub_count()-1].addProduct(pro_name,pro_price,pro_count);
                    }


                }

                else if(decision == 2)
                {
                    cout<<"Enter the sub-category of the product to be deleted : ";
                    fflush(stdin);
                    string sub_del;
                    getline(cin,sub_del);
                    int sub_i = -1;
                    for(int i=0;i<shops[index].return_sub_count();i++)
                    {
                        if(shops[index].obj_sub[i].return_sub_name()==sub_del)
                        {
                            sub_i = i;
                            break;
                        }
                    }
                    if(sub_i == -1)
                    {
                        cout<<"No such sub-category found!!"<<endl<<endl;
                        continue;
                    }
                    else{
                        cout<<"Enter the name of the product to be deleted : ";
                        string pro_del;
                        fflush(stdin);
                        getline(cin,pro_del);
                        int pro_i = -1;
                        for(int j=0;j<shops[index].obj_sub[sub_i].return_distinct_product();j++)
                        {
                            if(shops[index].obj_sub[sub_i].objects_pro[j].return_name()==pro_del)
                            {
                                pro_i = j;
                                break;
                            }
                        }
                        if(pro_i == -1)
                        {
                            cout<<"No such product found."<<endl<<endl;
                            continue;
                        }
                        else
                        {
                            for(int j=pro_i;j<shops[index].obj_sub[sub_i].return_distinct_product()-1;j++)
                            {
                                shops[index].obj_sub[sub_i].objects_pro[j] = shops[index].obj_sub[sub_i].objects_pro[j+1];
                            }
                            shops[index].obj_sub[sub_i].decrease_distinct_product();
                        }
                    }
                }
            }
        }
    }

void seller(shop* shops,int count_of_shops){
int decision=0;
        while(decision!=2){
            cout<<"1.LOGIN "<<endl;
            cout<<"2.Proceed to main menu"<<endl;
            cout<<"ENTER CHOICE : ";
            cin>>decision;
            if(decision==1){
                system("CLS");
                account(shops,count_of_shops);
            }
            else if(decision==2){
                system("CLS");
                break;
            }
        }

}

void customer(shop *shops,int count_of_shops)
{
            int decision = 0;
            while(decision!=5)
            {
                //system("CLS");
                cout<<"1.To search a Product."<<endl;
                cout<<"2.To see all the products in a particular store."<<endl;
                cout<<"3.To see the types of product available here."<<endl;
                cout<<"4.To see all the store present."<<endl;
                cout<<"5.To return to main menu"<<endl;
                fflush(stdin);
                cout<<"Enter your choice :: ";
                cin>>decision;
                if(decision==1)
                {
                    cout<<"Enter the product name to be searched : ";
                    string sea;
                    bool found[2] ;
                    found[0]= false;
                    found[1] = false;
                    fflush(stdin);
                    getline(cin,sea);
                    vector<string> id_store;
                    for(int i=0;i<count_of_shops;i++)
                    {
                        int sublen = shops[i].return_sub_count();
                        for(int j=0;j<sublen;j++)
                        {
                            int product_count = shops[i].obj_sub[j].return_distinct_product();
                            for(int k=0;k<product_count;k++)
                            {
                                if(shops[i].obj_sub[j].objects_pro[k].return_name()==sea)
                                {
                                    if(found[1]==false)
                                    {
                                        found[1]=true;
                                        product_found_decorator();
                                    }
                                    cout<<"THIS PRODUCT IS AVAILABLE AT "<<shops[i].name<<"SHOP"<<endl;
                                    cout<<"LOCATION OF THE SHOP IS :"<<shops[i].shop_address<<endl;
                                    cout<<"PRICE OF THIS PRODUCT AT THIS SHOP IS: "<<shops[i].obj_sub[j].objects_pro[k].return_price()<<endl;
                                    cout<<endl<<endl;
                                    found[0] = true;
                                    break;
                                }
                            }
                            if(found[0] ==true){
                                found[0] = false;
                                break;
                            }
                        }
                    }
                }

                else if(decision==2){
                    cout<<"Enter the Store Name : ";
                    string store;
                    fflush(stdin);
                    getline(cin,store);
                    int shop_num = -1;
                    for(int i=0;i<count_of_shops;i++)
                    {
                        if(shops[i].return_shop_name()==store)
                        {
                            shop_num = i;
                            break;
                        }
                    }
                    if(shop_num != -1)
                    {
                        cout<<"The shop "<<shops[shop_num].return_shop_name()<<" sells the following products :"<<endl;
                        for(int i=0;i<shops[shop_num].return_sub_count();i++)
                        {
                            cout<<"Category : "<<shops[shop_num].obj_sub[i].return_sub_name()<<endl;
                            for(int j=0;j<shops[shop_num].obj_sub[i].return_distinct_product();j++)
                            {
                                cout<<j+1<<". "<<shops[shop_num].obj_sub[i].objects_pro[j].return_name()<<endl;
                            }
                        }
                    }
                    else{
                        cout<<"Non such Store exists."<<endl;
                    }
                }

                else if(decision==3)
                {
                    cout<<"Enter the Store Name : ";
                    string store;
                    fflush(stdin);
                    getline(cin,store);
                    int shop_num = -1;
                    for(int i=0;i<count_of_shops;i++)
                    {
                        if(shops[i].return_shop_name()==store)
                        {
                            shop_num = i;
                            break;
                        }
                    }
                    if(shop_num != -1)
                    {
                        cout<<"The shop "<<shops[shop_num].return_shop_name()<<" sells the following types of products :"<<endl;
                        for(int i=0;i<shops[shop_num].return_sub_count();i++)
                        {
                            cout<<i+1<<". "<<shops[shop_num].obj_sub[i].return_sub_name()<<endl;
                        }
                    }
                    else{
                        cout<<"Non such Store exists."<<endl;
                    }
                }

                else if(decision==4)
                {
                    for(int i=0;i<count_of_shops;i++)
                    {
                        cout<<"The data for shop "<<i+1<<" is : "<<endl;
                        cout<<"Name : "<<shops[i].return_shop_name()<<endl;
                        cout<<"Address : "<<shops[i].return_shopadd()<<endl;
                    }
                }
            }
}

pair<shop*,int> read_file_data_to_object()
{
    fstream read("NEIL.txt",ios::in);
    int count_of_shops=0;
    while(read.good())
    {
        string a;
        getline(read,a);
        count_of_shops +=1;
    }
    shop * shops = new shop[count_of_shops];
    read.seekg(0,ios::beg);
    int j=0;
    cout<<"entering loop"<<endl;
    while(read.good()){
        string shop_data;
        getline(read,shop_data);
        cout<<"reading data of one line::"<<endl;

        stringstream line(shop_data);
        string temp;
        int k=0;
        while(line.good()){
            getline(line,temp,';');
            if(k==0){

                shops[j].set_id(temp);
                cout<<"setting shop id :"<<temp<<endl;
                k= k+1;
                continue;
            }
            else if(k==1){

                shops[j].set_password(temp);
                cout<<"setting up password :"<<temp<<endl;
                k=k+1;
                continue;
            }
            else if(k==2){
                cout<<"setting shop name :"<<temp<<endl;
                shops[j].set_shopname(temp);
                k=k+1;
                continue;
            }

            else if(k==3){

                shops[j].set_shop_address(temp);
                cout<<"setting shop address :"<<temp<<endl;
                k=k+1;
                continue;
            }

            else if(k==4){

                shops[j].set_category(temp);
                cout<<"setting shop category :"<<temp<<endl;
                k=k+1;
                continue;
            }

            if(temp=="subcategory"&&k==5){
                    int scat_count = 0;
                while(temp=="subcategory"||line.good()){
                        string remarker = temp;
                        if(temp=="subcategory"){
                        getline(line,temp,';');
                        shops[j].increment_sub_count();
                        int iter = shops[j].return_sub_count();
                        //shops[j].obj_sub[iter-1].return_sub_name() = temp;
                        shops[j].obj_sub[iter-1].set_subcategory_name(temp) ;
                        cout<<"subcategory : "<<temp<<endl;
                        scat_count =0;
                        }
                        else{
                            scat_count +=1;
                        }
                         int iter = shops[j].return_sub_count();
                        shops[j].obj_sub[iter-1].update_distinct_product();
                        if(remarker=="subcategory"){
                        getline(line,temp,';');}
                        string product_name = temp;
                        getline(line,temp,';');
                        string product_rate = temp;
                        getline(line,temp,';');
                        string product_count =temp;
                        int c = shops[j].obj_sub[iter-1].return_distinct_product();
                        shops[j].obj_sub[iter-1].objects_pro[c-1].set_product_details(product_name,product_rate,product_count);
                        cout<<"setting name ,rate,count :"<<product_name<<" "<<product_rate<<" "<<product_count<<endl;
                        getline(line,temp,';');
                }
            }

            if(k==6){
                cout<<endl<<endl;
                break;
            }
            k=k+1;
        }
        cout<<endl<<endl;
        j=j+1;
    }
    pair<shop*,int> ret;
    ret.first =shops;
    ret.second= j;
    //Closing the file
    read.close();
    return ret;
}

//updating the file when program ends
void update_function(shop *shops, int count_of_shops){
    ofstream myfile("NEIL.txt");
    for(int i=0;i<count_of_shops;i++){
       //first, writing all the data members of the shop in vector
        vector<string> v1;
        v1.push_back(shops[i].return_id());
        ///v1.push_back(shops[i].return_passcode());
        v1.push_back(shops[i].return_password());

        v1.push_back(shops[i].return_shop_name());

         v1.push_back(shops[i].return_shopadd());
         v1.push_back(shops[i].return_shop_category());


        int sublen = shops[i].return_sub_count();
        for(int j=0; j<sublen;j++)
        {
        // writing, all the subcategory name;
            v1.push_back("subcategory");
            v1.push_back(shops[i].obj_sub[j].return_sub_name());
            int product_count = shops[i].obj_sub[j].return_distinct_product();

            for(int k=0; k<product_count ; k++)
            {
                v1.push_back(shops[i].obj_sub[j].objects_pro[k].return_name());
                v1.push_back(shops[i].obj_sub[j].objects_pro[k].return_price());
                v1.push_back(shops[i].obj_sub[j].objects_pro[k].return_count());
            }
        }

        for(int r=0;r<v1.size();r++){
            cout<<v1[r]<<";";
        }
        cout<<endl;

            for(int m=0;m<v1.size();m++){

                myfile << v1[m];
                if(m!=v1.size()-1){
                myfile << ';';
                }
            }
            if(i!=count_of_shops-1){
            myfile << endl;
            }
        v1.clear();
    }
}


int main()
{
    pair<shop*,int> shop_detail = read_file_data_to_object();

    shop * shops = shop_detail.first;
    int count_of_shops = shop_detail.second;

    cout<<"No. of shops : "<<count_of_shops<<endl;
    system("CLS");
    int decision =0;
    while(decision!=3){

        cout<<"1. To Enter Customer Account "<<endl;
        cout<<"2. To Enter Into Seller Account "<<endl;
        cout<<"3. To Exit"<<endl;
        cin>>decision;
        if(decision==3){
            break;
        }
        else if(decision==2){
            system("CLS");
            seller(shops,count_of_shops);

        }
        else if(decision==1){
            system("CLS");
            customer(shops,count_of_shops);

        }
        else{
            system("CLS");
            cout<<"Entered wrong choice "<<endl;

        }
    }
    update_function(shops,count_of_shops);
    return 0;
}

/*
1;password1;spencer;floor 2;clothing;subcategory;child tshirt;avengers tshirt;300;4;puma tshirt;1200;5
2;password2;croma;ground floor;electronics;subcategory;phones;mi note 4;12000;3;mi kt pro;34500;7;subcategory;laptops;dell g7 15;1100 dollar;9
3;password3;redtape;floor 2;footwear;subcategory;sparx;sparx special series c7;7000;23;sparx cver 200 series shoes;2068;5;subcategory;adidas original;adidas gazelle series 7 shoe;5000;9
4;password4;food;floor 3;food court;subcategory;aggarwal store;raj kachori;300;nan;doda barfi;500;nan;boondi laddoo;790;nan;subcategory;haldiram;pav bhaji;300;nan
5;password5;pepperfry;floor 1;furniture;subcategory;teak furniture;bed;30000;5;mattress;6700;84
*/
