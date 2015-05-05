#ifndef USER_H
#define USER_H
#include <iostream>
#include <string>
#include <sstream>

class User{
 public:
  User();
  User(std::string name, int age, double balance, int type, std::string password);
  virtual ~User();

  int getAge() const;
  double getBalance() const;
  std::string getName() const;
  void deductAmount(double amt);
  virtual void dump(std::ostream& os);

  std::string getPassword() const;

 private:
  std::string name_;
  int age_;
  double balance_;
  int type_;
  std::string password_;
};
#endif
