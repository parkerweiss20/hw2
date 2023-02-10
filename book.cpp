#include <sstream>
#include <iomanip>
#include <ostream>
#include "book.h"
#include "util.h"


Book::Book(const std::string name, double price, int qty, const std::string ISBN, const std::string author) :
        Product(std::string("book"), name, price, qty)
{
  ISBN_ = ISBN;
  author_ = author;

}
      
          

Book::~Book(){

}

std::set<std::string> Book::keywords() const{
  std::set<std::string> name_list = parseStringToWords(name_);
  std::set<std::string> author_list = parseStringToWords(author_);
  std::set<std::string> list = setUnion(name_list,author_list);
  list.insert(ISBN_);
  return list;
}

bool Book::isMatch(std::vector<std::string>& searchTerms) const{
    std::set<std::string> keywords = Book::keywords();
    for (const std::string& term : searchTerms) {
      for(std::set<std::string>::iterator it = keywords.begin(); it != keywords.end(); it++){
        if(keywords.find(term) != keywords.end()){
          return true;
        }
      }
    }
  return false;
}


std::string Book::displayString() const{
  std::string output = name_ + "\n" + "Author: " + author_ + " ISBN: " + ISBN_ + "\n" + std::to_string(price_) + " " + std::to_string(qty_) + " left.";
  return output;
}


void Book::dump(std::ostream& os) const{
  os << category_ << std::endl;
  os << name_ << std::endl;
  os << price_ << std::endl;
  os << qty_ << std::endl;
  os << ISBN_ << std::endl;
  os << author_ << std::endl;
}
