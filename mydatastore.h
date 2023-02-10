#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <string>
#include <set>
#include <map>
#include <queue>
#include <unordered_map>
#include <vector>
#include "product.h"
#include "user.h"
#include "datastore.h"


class MyDataStore : public DataStore{
public:
    MyDataStore();
    ~MyDataStore();

    /**
     * Adds a product to the data store
     */
    void addProduct(Product* p);

    /**
     * Adds a user to the data store
     */
    void addUser(User* u);

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
    std::vector<Product*> search(std::vector<std::string>& terms, int type);

    /**
     * Reproduce the database file from the current Products and User values
     */
    void dump(std::ostream& ofile);

    void displayCart(std::string username);

    void addToCart(std::string username, int index, std::vector<Product*> hits);

    void buyCart(std::string username);

  private:
    std::set<Product*> products;
    std::unordered_map<std::string, std::set<Product*>> keyword_map;
    std::map<std::string, User*> user_map;
    std::map<std::string, std::vector<Product*>> cart_map;
};

#endif