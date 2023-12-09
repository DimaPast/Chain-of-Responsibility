#include <iostream>
#include <string>
#include <Windows.h>


class Handler {
public:
    virtual void handleRequest(const std::string& request) = 0;
    virtual ~Handler() = default;
};


class ConcreteHandler1 : public Handler {
private:
    Handler* successor; 

public:
    ConcreteHandler1(Handler* successor) : successor(successor) {}

    void handleRequest(const std::string& request) override {
        if (request == "Type1") {
            std::cout << "ConcreteHandler1 обробляє запит типу 1." << std::endl;
        }
        else if (successor != nullptr) {
            successor->handleRequest(request);
        }
    }
};


class ConcreteHandler2 : public Handler {
private:
    Handler* successor; 

public:
    ConcreteHandler2(Handler* successor) : successor(successor) {}

    void handleRequest(const std::string& request) override {
        if (request == "Type2") {
            std::cout << "ConcreteHandler2 обробляє запит типу 2." << std::endl;
        }
        else if (successor != nullptr) {
            successor->handleRequest(request);
        }
    }
};


class Client {
private:
    Handler* handlerChain; 

public:
    Client(Handler* handler) : handlerChain(handler) {}

    void makeRequest(const std::string& request) {
        handlerChain->handleRequest(request);
    }
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
  
    Handler* handler1 = new ConcreteHandler1(nullptr);
    Handler* handler2 = new ConcreteHandler2(handler1);

   
    Client client(handler2);

    
    client.makeRequest("Type1");
    client.makeRequest("Type2");
    client.makeRequest("Type3");

    delete handler1;
    delete handler2;

    return 0;
}