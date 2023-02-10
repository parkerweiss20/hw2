#include <sstream>
#include <iomanip>
#include <ostream>
#include "movie.h"
#include "util.h"


Movie::Movie(const std::string name, double price, int qty, const std::string genre, const std::string rating) :
        Product(std::string("movie"), name, price, qty),  genre_(genre), rating_(rating)
{

}
      
          

Movie::~Movie(){

}

std::set<std::string> Movie::keywords() const{
  std::set<std::string> name_list = parseStringToWords(name_);
  std::set<std::string> genre_list;
  genre_list.insert(convToLower(genre_));
  std::set<std::string> list = setUnion(name_list,genre_list);
  return list;
}

bool Movie::isMatch(std::vector<std::string>& searchTerms) const{
    std::set<std::string> keywords = Movie::keywords();
    for (const std::string& term : searchTerms) {
      for(std::set<std::string>::iterator it = keywords.begin(); it != keywords.end(); it++){
        if(keywords.find(term) != keywords.end()){
          return true;
        }
      }
    }
  return false;
}


std::string Movie::displayString() const{
  std::string output = name_ + "\n" + "Genre: " + genre_ + " Rating: " + rating_ + "\n" + std::to_string(price_) + " " + std::to_string(qty_) + " left.";
  return output;
}


void Movie::dump(std::ostream& os) const{
  os << category_ << std::endl;
  os << name_ << std::endl;
  os << price_ << std::endl;
  os << qty_ << std::endl;
  os << genre_ << std::endl;
  os << rating_ << std::endl;
}