#include <iostream>
#include <vector>
using namespace std;

class Stock
{
public:
    Stock(const string& code, int quantity) : m_code(code), m_quantity(quantity)
    {}

    void sell()
    {
        cout << "sell stock: code = " << m_code << " quantity = " << m_quantity << endl;
    }

    void buy()
    {
        cout << "buy stock: code = " << m_code << " quantity = " << m_quantity << endl;
    }

private:
    string m_code;
    int m_quantity;
};

class Order
{
public:
    virtual ~Order() {}
    virtual void execute() = 0;
};

class BuyStock : public Order
{
public:
    BuyStock(const Stock& stock) : m_stock(stock) {}
    void execute() { m_stock.buy(); }

private:
    Stock m_stock;
};

class SellStock : public Order
{
public:
    SellStock(const Stock& stock) : m_stock(stock) {}
    void execute() { m_stock.sell(); }

private:
    Stock m_stock;
};

class Broker
{
public:
    void addOrder(Order* order) { m_orders.push_back(order); }
    void placeOrders()
    {
        for (auto it = m_orders.cbegin(); it != m_orders.cend(); ++it)
        {
            (*it)->execute();
        }
    }

private:
    vector<Order*> m_orders;
};

int main()
{
    Broker broker;
    Stock stock("600000", 1000);

    Order* buyStock = new BuyStock(stock);
    Order* sellStock = new SellStock(stock);

    broker.addOrder(buyStock);
    broker.addOrder(sellStock);
    broker.placeOrders();

    delete buyStock;
    delete sellStock;

    cout << "Hello World!" << endl;
    return 0;
}
