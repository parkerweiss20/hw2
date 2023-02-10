#include <string>
#include <set>
#include <vector>
#include <ostream>
#include "mydatastore.h"
#include "util.h"


MyDataStore::MyDataStore(){

}

MyDataStore::~MyDataStore(){
  for (std::set<Product*>::iterator it = products.begin(); it != products.end(); ++it) {
    delete *it;
  }
  products.clear();

  for(std::map<std::string, User*>::iterator it = user_map.begin(); it != user_map.end(); ++it) {
    delete it->second;
  }
  user_map.clear();
  cart_map.clear();
}

void MyDataStore::addProduct(Product* p){
  for (const std::string& keyword : p->keywords()) {
      keyword_map[keyword].insert(p);
  }
  products.insert(p);
}

void MyDataStore::addUser(User* u){
  user_map[u->getName()] = u;
  std::vector<Product*> productQueue = std::vector<Product*>();
  cart_map[u->getName()] = productQueue;
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type){
  std::set<Product*> temp;
  std::vector<Product*> hits;
  
    if (terms.size() == 0)
  {
    std::cout << "No terms provided" << std::endl; 
    std::vector<Product*> empty; 
    return empty; 
  }
  if (type != 1 && type != 0)
  {
    std::cout << "Error, unknown type of search!" << std::endl;
    std::vector<Product*> empty;  
    return empty; 
  }

  for (unsigned int i = 0; i < terms.size(); i++)
  {
      terms[i] = convToLower(terms[i]); 
  }
  if (type == 1)  
  {
    temp = keyword_map[terms[0]]; 

    for (unsigned int i = 1; i < terms.size(); i++)
    {
      temp = setUnion(temp, keyword_map[terms[i]]); 
    } 
    std::vector<Product*> temp2(temp.begin(), temp.end());
    hits = temp2;  
  }
  else if (type == 0)  
  {
    temp = keyword_map[terms[0]]; 
    for (unsigned int q = 0; q < terms.size(); q++)
    {
      temp = setIntersection(temp, keyword_map[terms[q]]); 
    } 
    std::vector<Product*> temp2(temp.begin(), temp.end()); 
    hits = temp2;  
  }
  return hits; 
}


void MyDataStore::dump(std::ostream& ofile){
  ofile << "<products>" << std::endl;
  for (std::set<Product*>::iterator it = products.begin(); it != products.end(); ++it) {
  (*it)->dump(ofile);
  }
  ofile << "</products>" << std::endl;
  ofile << "<users>" << std::endl;
  for (std::map<std::string, User*>::iterator it = user_map.begin(); it != user_map.end(); ++it) {
    (it->second)->dump(ofile);
  }
  ofile << "</users>" << std::endl;
}


void MyDataStore::displayCart(std::string username){
  if (cart_map.find(username) == cart_map.end()) {
    std::cout << "Invalid username" << std::endl;
    return;
  }
  std::vector<Product*> user_cart = cart_map.find(username)->second;
  //int count = 1;


    int x = 1; //to list the item numbers 
    for (std::vector<Product*>::iterator it = cart_map[username].begin(); it != cart_map[username].end(); ++it) //iterate thru user's cart 
    {
      std::cout << "Item " << x++ << std::endl //cout Item x and then the item.displaystring shit
           << (*it)->displayString() << std::endl;
    }

/*
  while (!user_cart.empty()) {
    Product* curr_product = user_cart.front();
    std::cout << "Item " << count << std::endl;
    curr_product->displayString();
    user_cart.pop();
    count++;
    }

*/
}

void MyDataStore::addToCart(std::string username, int index, std::vector<Product*> hits){
  if (cart_map.find(username) == cart_map.end()) {
    std::cout << "Invalid request" << std::endl;
    return;
  }
  else{
    cart_map.find(username)->second.push_back(hits[index]);
  }
}

void MyDataStore::buyCart(std::string username){
  if (cart_map.find(username) == cart_map.end()) {
    std::cout << "Invalid username" << std::endl;
    return;
  }
  std::vector<Product*> user_cart = cart_map.find(username)->second;
  std::vector<Product*> leftover_cart;
  User* curr_user = user_map.find(username)->second;
  while(!user_cart.empty()){
    if(curr_user->getBalance() >= user_cart.front()->getPrice() && user_cart.front()->getQty() > 0){
      curr_user->deductAmount(user_cart.front()->getPrice());
      user_cart.front()->subtractQty(1);
      user_cart.erase(user_cart.begin());
    }
    else{
      leftover_cart.push_back(user_cart.front());
      user_cart.erase(user_cart.begin());
    }
  }
  cart_map.find(username)->second = leftover_cart;
}