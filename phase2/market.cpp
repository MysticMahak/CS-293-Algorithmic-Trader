#include "market.h"
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<sstream>

struct Tradelines_Sell{
    int price;
    int time;
    std::string owner;
    int line_num;

    // Constructor
    Tradelines_Sell(int a, int b, std::string c, int d) : price(a), time(b), owner(c), line_num(d) {}

    // Overload the < operator
    bool operator<(const Tradelines_Sell& other) const {
        if (price != other.price)
            return price > other.price; // Higher price has higher priority
        if (time != other.time)
            return time < other.time;  // Higher time has lower priority
        return owner < other.owner;  // Alphabetical order of tradername
    }
};

class Priority_Queue_Sell {
private:
    std::vector<Tradelines_Sell> data;

    void heapifyUp(int index) {
        while (index > 0) {
            int parentIndex = (index - 1) / 2;
            if (data[index] < data[parentIndex]) {
                std::swap(data[index], data[parentIndex]);
                index = parentIndex;
            } else {
                break;
            }
        }
    }

    void heapifyDown(int index) {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int smallest = index;

        if (leftChild < data.size() && data[leftChild] < data[smallest]) {
            smallest = leftChild;
        }

        if (rightChild < data.size() && data[rightChild] < data[smallest]) {
            smallest = rightChild;
        }

        if (smallest != index) {
            std::swap(data[index], data[smallest]);
            heapifyDown(smallest);
        }
    }

    int parent(int index) { return (index - 1) / 2; }
    int leftChild(int index) { return 2 * index + 1; }
    int rightChild(int index) { return 2 * index + 2; }

public:
    Priority_Queue_Sell() {}

    void push(Tradelines_Sell value) {
        data.push_back(value);
        heapifyUp(data.size() - 1);
    }

    void pop() {
        data[0] = data.back();
        data.pop_back();
        heapifyDown(0);
    }

    Tradelines_Sell top() {
        return data[0];
    }

    bool empty() {
        return data.empty();
    }
};


struct Tradelines_Buy{
    int price;
    int time;
    std::string owner;
    int line_num;

    // Constructor
    Tradelines_Buy(int a, int b, std::string c, int d) : price(a), time(b), owner(c), line_num(d) {}

    // Overload the < operator
    bool operator<(const Tradelines_Buy& other) const {
        if (price != other.price)
            return price < other.price; // Higher price has higher priority
        if (time != other.time)
            return time < other.time; // Higher time has lower priority
        return owner < other.owner;  // Alphabetical order of trader name
    }
};

class Priority_Queue_Buy {
private:
    std::vector<Tradelines_Buy> data;

    void heapifyUp(int index) {
        while (index > 0) {
            int parentIndex = (index - 1) / 2;
            if (data[index] < data[parentIndex]) {
                std::swap(data[index], data[parentIndex]);
                index = parentIndex;
            } else {
                break;
            }
        }
    }

    void heapifyDown(int index) {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int smallest = index;

        if (leftChild < data.size() && data[leftChild] < data[smallest]) {
            smallest = leftChild;
        }

        if (rightChild < data.size() && data[rightChild] < data[smallest]) {
            smallest = rightChild;
        }

        if (smallest != index) {
            std::swap(data[index], data[smallest]);
            heapifyDown(smallest);
        }
    }

    int parent(int index) { return (index - 1) / 2; }
    int leftChild(int index) { return 2 * index + 1; }
    int rightChild(int index) { return 2 * index + 2; }

public:
    Priority_Queue_Buy() {}

    void push(Tradelines_Buy value) {
        data.push_back(value);
        heapifyUp(data.size() - 1);
    }

    void pop() {
        data[0] = data.back();
        data.pop_back();
        heapifyDown(0);
    }

    Tradelines_Buy top() {
        return data[0];
    }

    bool empty() {
        return data.empty();
    }
};

struct order{
    int timestamp;
    std::string trader;
    std::string signal;
    std::vector<std::pair<std::string, int>> stocks;
    int price;
    int total_quantity;
    int expiry_timestamp;
};

struct success_trade{
    std::string seller;
    std::string buyer;
};

struct everyTrader{
    std::string Tradername;
    int bought;
    int sold;
    int mone_change;
};


bool doesStringExist(const std::vector<std::pair<std::string, int>>& vec, const std::pair<std::string, int>& targetString) {
    bool nvm = false;
    for (const auto& pair : vec) {
        //std::cout << pair.first << std::endl;
        if (pair.first == targetString.first) {
            if( vec.size() == 1){ return true;}
            else{
                if( pair.second == targetString.second ) return true; // check if it is the same linear combination
            }
        }
    }
    return false;
}

market::market(int argc, char** argv){

}

void market::start(){
    std::vector<order> Trades;
    std::ifstream inputFile("output.txt");
    std::vector<everyTrader> trades_done;
    int total_trades= 0;
    int money_change = 0;
    int share_exchange = 0;

    if (!inputFile.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }
    std::string line;

    if (std::getline(inputFile, line)) {}

    while (std::getline(inputFile, line)) {
        // Check if the line contains "!@" and break if it does
        if (line.find("!@") != std::string::npos) {
            break;
        }

        // defining the data structure
        order new_order;

        int count = 0;
        std::stringstream ss(line);
        std::string word;

        while (ss >> word) {
            count ++;
        }

        std::istringstream iss(line);

        int z = 0;
        // Extract the first two fields
        iss >> new_order.timestamp >> new_order.trader >> new_order.signal;
        z += 3;
        //std::cout << new_order.timestamp << std::endl;
        // Process the rest of the fields
        
        std::string key;
        std::string value;
        while (iss >> key >> value) {
            z +=2;
            if (key.find('$') != std::string::npos || value.find('$') != std::string::npos) {
                break;
            }
            int data = std::stoi(value);
            new_order.stocks.push_back(std::make_pair(key, data)); 
        }
        if( count - z == 2 || count - z == 3){}
        else{ continue;}
        std::string str;

        if(new_order.stocks.size() == 0) {
            value = value.substr(1);
            new_order.price = std::stoi(value);

            iss >> str;
            str = str.substr(1);
            int greta = std::stoi(str);
            new_order.total_quantity = greta;
            new_order.stocks.push_back(std::make_pair(key, new_order.total_quantity));
        }
        else{

            key = key.substr(1);
            new_order.price = std::stoi(key);
            value = value.substr(1);
            new_order.total_quantity = std::stoi(value);
        }

        iss >> new_order.expiry_timestamp;

        // Logic starts here
        bool same_stocks = true;
        //int Tradeline = -1;
        success_trade final_trade;

        Priority_Queue_Sell Sell;
        Priority_Queue_Buy Buy;

        Trades.push_back(new_order);
        //std::cout << Trades.size() << std::endl;
        for( int i = 0; i < Trades.size(); i++){
            //std::cout << i << std::endl;
            if( (Trades[i].expiry_timestamp < 0) || (Trades[i].expiry_timestamp + Trades[i].timestamp) >= new_order.timestamp ){
                if(Trades[i].total_quantity > 0){
                if( new_order.signal == "BUY"){
                    if( Trades[i].signal == "SELL" && Trades[i].price <= new_order.price && Trades[i].stocks.size() == new_order.stocks.size()){
                        //std::cout << i << " " << Trades.size() << std::endl; 
                        same_stocks = true;
                        for (auto& element : new_order.stocks) { //std::cout<<element.first<<std::endl;
                            if(!doesStringExist(Trades[i].stocks, element)) {same_stocks = false;break;}
                        }
                        if( same_stocks ){  //std::cout << "Here" << std::endl;
                            // Choose which trade
                            Tradelines_Buy t(Trades[i].price, Trades[i].timestamp, Trades[i].trader, i); 
                            Buy.push(t);
                        }
                }
                }
                else{
                    if( Trades[i].signal == "BUY" && Trades[i].price >= new_order.price && Trades[i].stocks.size() == new_order.stocks.size()){
                        //std::cout << " Here " << std::endl;
                        same_stocks = true;
                        for (auto& element : new_order.stocks) {
                            if(!doesStringExist(Trades[i].stocks, element)) {same_stocks = false;break;}}

                        if( same_stocks ){//std::cout << "Here" << std::endl;
                        // Choose which trade 
                        Tradelines_Sell t(Trades[i].price, Trades[i].timestamp, Trades[i].trader, i);
                        Sell.push(t);
                    }
                }
                }
            }
            }
        } 
        //std::cout << Tradeline << std::endl;

        if(!Sell.empty()){ //KarGoKrab purchased 12 share of AMZN from KarGoCorp for $100/share
            while( !Sell.empty() && new_order.total_quantity != 0){
                Tradelines_Sell new_tarde = Sell.top();
                total_trades++;
                std::cout << Trades[new_tarde.line_num].trader << " purchased ";
                int final_val = std::min(Trades[new_tarde.line_num].total_quantity, new_order.total_quantity);
                
                if( final_val > 0) std::cout << final_val << " share of ";
                for (const auto& pair : new_order.stocks) {
                        std::cout << pair.first;
                }
                share_exchange += final_val;
                money_change += final_val*Trades[new_tarde.line_num].price;
                Trades[new_tarde.line_num].total_quantity -= final_val;
                new_order.total_quantity -= final_val;
                std::cout<<" from " << new_order.trader << " for $" << Trades[new_tarde.line_num].price << "/share" << std::endl;
                bool tr1 = false; bool tr2 = false;
                for (auto& pair : trades_done) {
                    if (pair.Tradername == Trades[new_tarde.line_num].trader){
                        tr1 = true; pair.bought += final_val; pair.mone_change -= final_val*Trades[new_tarde.line_num].price;
                    }
                    if( pair.Tradername == new_order.trader){
                        tr2 = true; pair.sold += final_val; pair.mone_change += final_val*Trades[new_tarde.line_num].price;
                    }
                }
                if( !tr1){
                    everyTrader ohdsj; ohdsj.Tradername = Trades[new_tarde.line_num].trader; ohdsj.bought = final_val; ohdsj.sold = 0;
                    ohdsj.mone_change = 0 - final_val*Trades[new_tarde.line_num].price; trades_done.push_back(ohdsj);
                }
                if( !tr2){
                    everyTrader ohdsj; ohdsj.Tradername = new_order.trader; ohdsj.sold = final_val; ohdsj.bought = 0;
                    ohdsj.mone_change = final_val*Trades[new_tarde.line_num].price; trades_done.push_back(ohdsj);
                }
                Sell.pop();
            }

        } //std::cout << "Why Segfault" << std::endl;

        else if(!Buy.empty()){ //std::cout << "Why Segfault" << std::endl;
            while( !Buy.empty() && new_order.total_quantity != 0){
                Tradelines_Buy new_tarde = Buy.top();
                Buy.pop();
                total_trades++;
                std::cout << new_order.trader << " purchased ";
                int final_val = std::min(Trades[new_tarde.line_num].total_quantity, new_order.total_quantity);
                if( final_val > 0) std::cout << final_val << " share of ";
                for (const auto& pair : new_order.stocks) {
                        std::cout << pair.first;
                }
                Trades[new_tarde.line_num].total_quantity -= final_val;
                new_order.total_quantity -= final_val;
                share_exchange += final_val;
                money_change += final_val*Trades[new_tarde.line_num].price;
                std::cout<<" from " << Trades[new_tarde.line_num].trader << " for $" << Trades[new_tarde.line_num].price << "/share" << std::endl;
                bool tr1 = false; bool tr2 = false;
                for (auto& pair : trades_done) {
                    if (pair.Tradername == Trades[new_tarde.line_num].trader){
                        tr1 = true; pair.sold += final_val; pair.mone_change += final_val*Trades[new_tarde.line_num].price;
                    }
                    if( pair.Tradername == new_order.trader){
                        tr2 = true; pair.bought += final_val; pair.mone_change -= final_val*Trades[new_tarde.line_num].price;
                    }
                }
                if( !tr1){
                    everyTrader ohdsj; ohdsj.Tradername = Trades[new_tarde.line_num].trader; ohdsj.sold = final_val; ohdsj.bought = 0;
                    ohdsj.mone_change = final_val*Trades[new_tarde.line_num].price; trades_done.push_back(ohdsj);
                }
                if( !tr2){
                    everyTrader ohdsj; ohdsj.Tradername = new_order.trader; ohdsj.bought = final_val; ohdsj.sold = 0;
                    ohdsj.mone_change = 0 - final_val*Trades[new_tarde.line_num].price; trades_done.push_back(ohdsj);
                }
            }
        }
        Trades[Trades.size()-1].total_quantity = new_order.total_quantity;
        //std::cout << "Why Segfault" << std::endl;
        //std::cout << Tradeline << std::endl;
        //std::cout << "Why Segfault" << std::endl;
    }
    inputFile.close(); // Close the file when done
    std::cout << "\n---End of Day---\n" << "Total Amount of Money Transferred: $" << money_change << "\n" << "Number of Completed Trades: " << total_trades << "\n";
    std::cout << "Number of Shares Traded: " << share_exchange << "\n";
    for( auto& element : trades_done){
        std::cout << element.Tradername << " bought " << element.bought << " and sold " << element.sold << " for a net transfer of $" << element.mone_change << std::endl;
    }
}
