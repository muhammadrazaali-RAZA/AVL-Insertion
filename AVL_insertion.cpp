#include <iostream>
#include <conio.h>
#include <stdlib.h>
using namespace std;

struct node
{
  int info;
  node *left,*right;
};

class bin_search_tree
{
   private :
	    node *temp;
   public  :
	    node *root;
	    int number;
	    bin_search_tree();
	    ~bin_search_tree();
	    void options();
	    void b_search_tree(node *);
	    void in_order(node *);
	    void b_delete(node *);
	    void destory(node *);
	    int height(node *);
	    void avl(node *);
};

int main()
{
  char ch;
  bin_search_tree obj;
  while( 4 )
  {
    obj.options();
    ch=getch();
    switch(ch)
     {
       	case '0':
			exit(0);
			break;
		
		case '1':
			obj.in_order(obj.root);
			break;
			
		case '2':
			cout<<"\n Enter number to add in a tree... \n";
			cin>>obj.number;
			obj.b_search_tree( obj.root );
			break;
		
		case '3':
			cout<<"\n Enter number to delete in a tree... \n";
			cin>>obj.number;
			obj.b_delete(obj.root);
			break;
		//case '4':
			
			//cout<<obj.height(obj.root);
			//break;
       	default :
       		obj.destory(obj.root);
			cout<<"Delete tree "<<endl;
			exit(0);
			break;
     } // end of switch.
  } // end of while.
}//-----------------------------------------------

bin_search_tree :: bin_search_tree()
{
  root=temp=NULL;
}
//--------------------------------------------------------
void bin_search_tree :: b_search_tree(node *temp)
{
  if( root==NULL )
   {
     temp=new node;
     temp->info = number;
     temp->left=NULL;
     temp->right=NULL;
     root=temp;
     return;
   }

  	if( temp->info==number )
   	{
      cout<<" \n Given number is already present in tree.\n";
      return;
    }
	if(temp->info > number)
	{
    	if( temp->left!=NULL )
       	{
			b_search_tree(temp->left);
			avl(temp);
			cout<<"store...!"<<endl;
			return;
       	}
      	else
       	{
	 		temp->left=new node;
	 		temp->left->info = number;
	 		temp->left->left=NULL;
	 		temp->left->right=NULL;
	 		return;
       	}
   	}
   	if(temp->info < number)
   	{
		if( temp->right!=NULL )
       	{
			b_search_tree( temp->right );
			cout<<"store...!"<<endl;
			avl(temp);
			return;
       	}
      	else
       	{
	 		temp->right=new node;
	 		temp->right->info = number;
	 		temp->right->left=NULL;
	 		temp->right->right=NULL;
	 		return;
       	}
   	}

} //--------------------    Insertion Function  Ends    --------------------------

//----------------------- Deletting Function Start  ----------------------

void bin_search_tree::b_delete(node *temp){
	if(temp->info > number){
		if(temp->left->info == number){
			if(temp->left->left==NULL && temp->left->right==NULL){            // ----------- Case 1 Start ----------
				delete temp->left;
				temp->left=NULL;
				return;
			}													    		 // ----------- Case 1 Ends  ----------
			if(temp->left->left!=NULL && temp->left->right==NULL){           // ----------- Case 2 Start ----------
				node *t;
				t=temp->left;
				temp->left=t->left;
				delete t;
				return;
			}
			if(temp->left->left==NULL && temp->left->right!=NULL){
				node *t;
				t=temp->left;
				temp->left=t->right;
				delete t;
				return;
			}																// ----------- Case 2 Ends -----------
			if(temp->left->left!=NULL && temp->left->right!=NULL){          // ----------- Case 3 Start ----------
				node *t=temp->left->right;
				if(t->left!=NULL){
					while(t->left->left!=NULL){
						t=t->left;
					}
					temp->left->info=t->left->info;
					number=t->left->info;
					b_delete(t);
					return;
				}
				temp->left->info=t->info;
				number=t->info;
				b_delete(temp->left);
				return;
			}																// ----------- Case 3 Ends ------------
		}else{
			b_delete(temp->left);
			return;
		}
	}else{
		if(temp->right->info == number){
			if(temp->right->left==NULL && temp->right->right==NULL){        // ----------- Case 1 Start ----------
				delete temp->right;
				temp->right=NULL;
				return;
			}				   	        								   // ----------- Case 1 Ends  ----------
			if(temp->right->left!=NULL && temp->right->right==NULL){           // ----------- Case 2 Start ----------
				node *t;
				t=temp->right;
				temp->right=t->left;
				delete t;
				return;
			}
			if(temp->right->left==NULL && temp->right->right!=NULL){
				node *t;
				t=temp->right;
				temp->right=t->right;
				delete t;
				return;
			}																// ----------- Case 2 Ends -----------
			if(temp->right->left!=NULL && temp->right->right!=NULL){          // ----------- Case 3 Start ----------
				node *t=temp->right->right;
				if(t->left!=NULL){
					while(t->left->left!=NULL){
						t=t->left;
					}
					temp->right->info=t->left->info;
					number=t->left->info;
					b_delete(t);
					return;
				}
				temp->right->info=t->info;
				number=t->info;
				b_delete(temp->right);
				return;
			}																// ----------- Case 3 Ends ------------
		}else{
			b_delete(temp->right);
			return;
		}
	}
}//----------------------- Deletting Function Ends  -----------------------




//----------------------- destory tree Function Starts  -----------------------

bin_search_tree::~bin_search_tree(){
	destory(root);
	cout<<"Done "<<endl;
}

void bin_search_tree::destory(node *temp){
	if(temp->left!=NULL && temp->right!=NULL){
		destory(temp->left);
		destory(temp->right);
		delete temp;
		temp=NULL;
		return;
	}

	
	else if(temp->left!=NULL && temp->right==NULL){
		destory(temp->left);
		delete temp;
		temp=NULL;
		return;
	}

	else if(temp->left==NULL && temp->right!=NULL){
		destory(temp->right);
		delete temp;
		temp=NULL;
		return;
	}
	
	else{
		delete temp;
		temp=NULL;
		return;
	}
	root=NULL;
}

//----------------------- Height Function Start  -----------------------
int bin_search_tree::height(node *temp){
	if(temp==NULL)
		return 0;
	if(temp->left==NULL && temp->right==NULL)
		return 1;
	
	else if(temp->left!=NULL && temp->right==NULL)
		return 1+height(temp->left);

	else if(temp->left==NULL && temp->right!=NULL)
		return 1+height(temp->right);
		
	else{
		int a=height(temp->left);
		int b=height(temp->right);
		if(a>b)
			return a+1;
		else
			return b+1;
	}
	return 0;
}
//----------------------- Hight Function Ends  -----------------------

//----------------------- destory tree Function Ends  -----------------------

void bin_search_tree :: options()
{
 	cout<<"\n\n ************** Select Option *****************.\n";
 	cout<<"\n Enter any of choices.\n";
 	cout<<"\n 0 : Quitting the Program.\n";
 	cout<<"\n 1 : Print the whole BST .\n";
 	cout<<"\n 2 : Adding (inserting) node in BST.\n";
 	cout<<"\n 3 : Deletting (deleshion) node in BST.\n";
 	//cout<<"\n 4 : height of root in tree...\n";
}//--------------------------------------------------------------
void bin_search_tree :: in_order(node *temp)
{
  if(root==NULL)
    {
	cout<<" Tree is empty.\n";
	return;
    }
  if( temp->left!=NULL ){
  	cout<<"("<<temp->info<<")left->";
  	in_order(temp->left);
  }
    		 
  cout<<temp->info<<"  ";
  if( temp->right!=NULL ){
  	cout<<"("<<temp->info<<")right->";
  	in_order(temp->right);
  }
		 
  return;
}//----------------------------    PROGRAM ENDS HERE  ---------------------------------------



//////////////////////////////////-----------------------------------//////////////////////////////////////
void bin_search_tree::avl(node *temp){
			if(temp->left==NULL)
				return;
				
			if(temp->right==NULL)
				return;
					
			int level;
			level=height(temp->left->left)-height(temp->left->right);
			cout<<"temp->left :  "<<level<<endl;
			if(level<-1){
				level=height(temp->left->right->left)-height(temp->left->right->right);
				cout<<"temp->left->right:  "<<level<<endl;
				node *t;
				if(level>0){
					/////   ZIC ZAC  ///// 1
					t=temp->left->right->left;
					temp->left->right->left=t->right;
					t->right=temp->left->right;
					temp->left->right=t;
					//////  repeat  ///// 2
					t=temp->left->right;
					temp->left->right=t->left;
					t->left=temp->left;
					temp->left=t;
					cout<<"temp->left->right->left has change ...!"<<endl;
				}else{
					t=temp->left->right;
					temp->left->right=t->left;
					t->left=temp->left;
					temp->left=t;
					cout<<"temp->left->right->right has change ...!"<<endl;
				}
			}
			if(level>1){
				level=height(temp->left->left->left)-height(temp->left->left->right);
				cout<<"temp->left->left:  "<<level<<endl;
				node *t;
				if(level<0){
					/////   ZIC ZAC  ///// 1
					t=temp->left->left->right;
					temp->left->left->right=t->left;
					t->left=temp->left->left;
					temp->left->left=t;
					//////  repeat  ///// 2
					t=temp->left->left;
					temp->left->left=t->right;
					t->right=temp->left;
					temp->left=t;
					cout<<"temp->left->left->right has change ...!"<<endl;
				}else{
					t=temp->left->left;
					temp->left->left=t->right;
					t->right=temp->left;
					temp->left=t;
					cout<<"temp->left->left->left has change ...!"<<endl;
				}
			}
			////    Left side Ends     /////////////
			
			////    Right side      ///////////
			

	
			level=height(temp->right->left)-height(temp->right->right);
			cout<<"temp->right:  "<<level<<endl;
			if(level<-1){
				level=height(temp->right->right->left)-height(temp->right->right->right);
				cout<<"temp->right->right:  "<<level<<endl;
				node *t;
				if(level>0){
					/////   ZIC ZAC  ///// 1
					t=temp->right->right->left;
					temp->right->right->left=t->right;
					t->right=temp->right->right;
					temp->right->right=t;
					//////  repeat  ///// 2
					t=temp->right->right;
					temp->right->right=t->left;
					t->left=temp->right;
					temp->right=t;
					cout<<"temp->right->right->left has change ...!"<<endl;
				}else{
					t=temp->right->right;
					temp->right->right=t->left;
					t->left=temp->right;
					temp->right=t;
					cout<<"temp->right->right->right has change ...!"<<endl;
				}
			}
			if(level>1){
				level=height(temp->right->left->left)-height(temp->right->left->right);
				cout<<"temp->right->left:  "<<level<<endl;
				node *t;
				if(level<0){
					/////   ZIC ZAC  ///// 1
					t=temp->right->left->right;
					temp->right->left->right=t->left;
					t->left=temp->right->left;
					temp->right->left=t;
					//////  repeat  ///// 2
					t=temp->right->left;
					temp->right->left=t->right;
					t->right=temp->right;
					temp->right=t;
					cout<<"temp->right->left->right has change ...!"<<endl;
				}else{
					t=temp->right->left;
					temp->right->left=t->right;
					t->right=temp->right;
					temp->right=t;
					cout<<"temp->right->left->left has change ...!"<<endl;
				}
			}
			/////// Right side ENDS ///////////////////	
			/////// if temp equal to Root  Start/////////////
			if(temp==root){
				if(root->left==NULL)
					return;
					
				if(root->right==NULL)
					return;
						
				int level;
				level=height(root->left)-height(root->right);
				cout<<"root :  "<<level<<endl;
				if(level<-1){
					level=height(root->right->left)-height(root->right->right);
					cout<<"root->right:  "<<level<<endl;
					node *t;
					if(level>0){
						/////   ZIC ZAC  ///// 1
						t=root->right->left;
						root->right->left=t->right;
						t->right=root->right;
						root->right=t;
						//////  repeat  ///// 2
						t=root->right;
						root->right=t->left;
						t->left=root;
						root=t;
						cout<<"root->right->left has change ...!"<<endl;
					}else{
						t=root->right;
						root->right=t->left;
						t->left=root;
						root=t;
						cout<<"root->right->right has change ...!"<<endl;
					}
				}
				if(level>1){
					level=height(root->left->left)-height(root->left->right);
					cout<<"root->left:  "<<level<<endl;
					node *t;
					if(level<0){
						/////   ZIC ZAC  ///// 1
						t=root->left->right;
						root->left->right=t->left;
						t->left=root->left;
						root->left=t;
						//////  repeat  ///// 2
						t=root->left;
						root->left=t->right;
						t->right=root;
						root=t;
						cout<<"root->left->right has change ...!"<<endl;
					}else{
						t=root->left;
						root->left=t->right;
						t->right=root;
						root=t;
						cout<<"root->left->left has change ...!"<<endl;
					}
				}
			}
			
			/////// if temp equal to Root Ends///////////////
			
		return;
}
