// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

std::string infx2pstfx(std::string inf) {
  TStack<char, 100> stack1;
  std::string vih;
  std::string post;
  for (int i = 0; i < inf.length(); i++) {
    if (4 == prioritet(inf[i])) {
      vih += (inf[i]);
      while (4 == prioritet(inf[i + 1]) && i+1 < inf.length()) {
        vih += (inf[i + 1]);
        i++;
      }
      vih += ' ';
    }  else {
        if (0 == prioritet(inf[i])) {
          stack1.push(inf[i]);
       } else if (prioritet(inf[i]) > prioritet(stack1.get())) {
           stack1.push(inf[i]);
         } else if (stack1.isEmpty()) {
             stack1.push(inf[i]);
           } else if (1 == prioritet(inf[i])) {
               while (0 != prioritet(stack1.get())) {
                 vih += (stack1.get());
                 vih += ' ';
                 stack1.pop();
               }
               stack1.pop();
             } else if (prioritet(inf[i]) <= prioritet(stack1.get())) {
                 while (!stack1.isEmpty() && 1 < prioritet(stack1.get())) {
                   vih += (stack1.get());
                   vih += (' ');
                   stack1.pop();
                 }
                 stack1.push(inf[i]);
               }
     }
  }
  while (!stack1.isEmpty()) {
    vih += (stack1.get());
    vih += (' ');
    stack1.pop();
  }
  vih.pop_back();
  post = vih;
  return post;
}

int eval(std::string post) {
  TStack<int, 100> stack2;
  std::string vih;
  int vivod = 0;
  for (int i = 0; i < post.length(); i++) {
    std::string check = "";
    while (prioritet(post[i]) == 4) {
      check += (post[i]);
      i++;
    }
    if (check != "") {
      stack2.push(std::stoi(check));
    }
    if (prioritet(post[i]) == 2 || prioritet(post[i]) == 3) {
      int chlen1 = stack2.get();
      stack2.pop();
      int chlen2 = stack2.get();
      stack2.pop();
      if (post[i] == '-') {
        vivod = chlen2 - chlen1;
        stack2.push(vivod);
      } else if (post[i] == '+') {
          vivod = chlen1 + chlen2;
          stack2.push(vivod);
        } else if (post[i] == '*') {
            vivod = chlen1 * chlen2;
            stack2.push(vivod);
          } else if (post[i] == '/') {
              vivod = chlen2 / chlen1;
              stack2.push(vivod);
            }
    }
  }
  vivod = stack2.get();
  return vivod;
}
