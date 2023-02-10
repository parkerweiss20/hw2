#include <sstream>
#include <iomanip>
#include <ostream>
#include "clothing.h"
#include "util.h"


Clothing::Clothing(const std::string name, double price, int qty, const std::string size, const std::string brand) :
        Product(std::string("clothing"), name, price, qty),  size_(size), brand_(brand)
{

}
      
          

Clothing::~Clothing(){

}

std::set<std::string> Clothing::keywords() const{
  std::set<std::string> name_list = parseStringToWords(convToLower(name_));
  std::set<std::string> brand_list = parseStringToWords(convToLower(brand_));
  std::set<std::string> list = setUnion(name_list,brand_list);
  list.insert(convToLower(size_));
  return list;
}

bool Clothing::isMatch(std::vector<std::string>& searchTerms) const{
    std::set<std::string> keywords = Clothing::keywords();
    for (const std::string& term : searchTerms) {
      for(std::set<std::string>::iterator it = keywords.begin(); it != keywords.end(); it++){
        if(keywords.find(term) != keywords.end()){
          return true;
        }
      }
    }
  return false;
}


std::string Clothing::displayString() const{
  std::string output = name_ + "\n" + "Size: " + size_ + " Brand: " + brand_ + "\n" + std::to_string(price_) + " " + std::to_string(qty_) + " left.";
  return output;
}


void Clothing::dump(std::ostream& os) const{
  os << category_ << std::endl;
  os << name_ << std::endl;
  os << price_ << std::endl;
  os << qty_ << std::endl;
  os << size_ << std::endl;
  os << brand_ << std::endl;
}