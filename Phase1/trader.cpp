#include "receiver.h"
#include <map>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <string>
#include <fstream>
void part1(const std::string& message,std::map<std::string, std::pair<int, char>>& stock_lastord, std::map<std::string, std::pair<int, char>>& stock_lastord_buy, std::map<std::string, std::pair<int, char>>& stock_lastord_sell){
    std::string stock;
    int price;
    char signal;
    std::string currentLine = "";
    for (char c : message) {
   //Loop through each character in the input message
        if (c == '#') {
            //If a # is encountered, process the current line as trading message 
            // Read fields separated by spaces
            std::istringstream stream(currentLine);
            stream >> stock >> price >> signal;

            if (signal == 'b'){
                auto it = stock_lastord.find(stock);
                if (it == stock_lastord.end()){
        //If stock is not present,create entries
                    stock_lastord_buy[stock] = std::make_pair(price, 's');
                    stock_lastord[stock] = std::make_pair(price, 's');
                    signal = 's';
                    std::cout << stock << " " << price << " " << signal << "\n";}
                else{
                //If stock is already present,update entries based on trading logic
                    auto it = stock_lastord_sell.find(stock);
                    if (it == stock_lastord_sell.end()){
                    //If no sell order is present,check conditions for updating buy order
                        if( price <= stock_lastord_buy[stock].first){
                            std::cout << "No Trade\n";
                        }
                        else{
                            signal = 's'; stock_lastord_buy[stock] = std::make_pair(price, signal);
                            if(stock_lastord[stock].second == 'b'){
                                if(price > stock_lastord[stock].first) {
                                    signal = 's'; stock_lastord[stock] = std::make_pair(price, signal);
                                    std::cout << stock << " " << price << " " << signal << "\n";
                                }
                                else std::cout << "No Trade\n";}
                            else{
                                signal = 's'; stock_lastord[stock] = std::make_pair(price, signal);
                                std::cout << stock << " " << price << " " << signal << "\n";
                            }
                        }
                    }
                    else{
                    //If a sell order is present,update entries based on trading logic
                        if( price <= stock_lastord_buy[stock].first){
                            std::cout << "No Trade\n";
                        }
                        else if( price == stock_lastord_sell[stock].first){
                            stock_lastord_sell.erase(stock);     // The last order has been removed now
                            std::cout << "No Trade\n";
                        }
                        else{
                            signal = 's'; stock_lastord_buy[stock] = std::make_pair(price, signal);
                            if(stock_lastord[stock].second == 'b'){
                                if(price > stock_lastord[stock].first) {
                                    signal = 's'; stock_lastord[stock] = std::make_pair(price, signal);
                                    std::cout << stock << " " << price << " " << signal << "\n";
                                }
                                else std::cout << "No Trade\n";}
                            else{
                                signal = 's'; stock_lastord[stock] = std::make_pair(price, signal);
                                std::cout << stock << " " << price << " " << signal << "\n";
                            }
                        }
                    }
                }
            }
            else {
                auto it = stock_lastord.find(stock);
                if (it == stock_lastord.end()){ 
                //If stock is not ppresent in the order book, create entries
                    signal = 'b';
                    std::cout << stock << " " << price << " " << signal << "\n";
                    stock_lastord_sell[stock] = std::make_pair(price, 'b');
                    stock_lastord[stock] = std::make_pair(price, 'b');}
                else{ 
                // If the stock is already present, update entries based on trading logic
                    auto it = stock_lastord_sell.find(stock);
                    if (it == stock_lastord_sell.end()){
                   // If no sell order is present, check conditions for updating buy order 
                        if( price == stock_lastord_buy[stock].first){
                            stock_lastord_buy.erase(stock);     // The last order has been removed now
                            std::cout << "No Trade\n"; 
                        }
                        else{
                            signal = 'b'; stock_lastord_sell[stock] = std::make_pair(price, signal);
                            if(stock_lastord[stock].second == 's'){
                                if(price < stock_lastord[stock].first) {
                                    signal = 'b'; stock_lastord[stock] = std::make_pair(price, signal);
                                    std::cout << stock << " " << price << " " << signal << "\n";
                                }
                                else std::cout << "No Trade\n"; 
                                }
                            else if(stock_lastord[stock].second == 'b' && signal == 's'){
                                signal = 'b'; stock_lastord[stock] = std::make_pair(price, signal);
                                std::cout << stock << " " << price << " " << signal << "\n";}
                        }
                    }
                    else{
                    // If a sell order is present, update entries based on trading logic
                    if( price > stock_lastord_sell[stock].first){
                        //std::cout << stock_lastord_sell[stock].first;
                        std::cout << "No Trade\n";
                    }
                    else if( price == stock_lastord_buy[stock].first){
                        stock_lastord_buy.erase(stock);     // The last order has been removed now
                        std::cout << "No Trade\n"; 
                    }
                    else{
                        signal = 'b'; stock_lastord_sell[stock] = std::make_pair(price, signal);
                        if(stock_lastord[stock].second == 's'){
                            if(price < stock_lastord[stock].first) {
                                signal = 'b'; stock_lastord[stock] = std::make_pair(price, signal);
                                std::cout << stock << " " << price << " " << signal << "\n";
                            }
                            else std::cout << "No Trade\n"; 
                        }
                        else if(stock_lastord[stock].second == 'b'){
                            signal = 'b'; stock_lastord[stock] = std::make_pair(price, signal);
                            std::cout << stock << " " << price << " " << signal << "\n";
                    }
                    }
                }
                }
            }

            currentLine = "";}

        else {
            // If '#' is not encountered,append the character to the current line
            currentLine += c;
        }
    }
}

struct order{
    char signal;
    std::vector<std::string> stocks;
    int price;
    char validity;
};

void outputMap(const std::map<std::string, std::vector<int>>& myMap) {
    for (const auto& pair : myMap) {
        std::cout << pair.first << ": ";
        for( int i = 0; i < pair.second.size(); i++){
            std::cout << pair.second[i] << " ";
        }
        std::cout << "\n";
    }
}

void checkLinearCombo(std::vector<int>& subset, std::vector<bool>& valid,const std::map<std::string, std::vector<int>>& Dealdeal,const std::vector<int>& prices,const std::vector<char>& signals,std::vector<std::string>& all_lines, std::vector<std::pair<std::vector<std::string>, int>>& arbitrage_lines, std::vector<std::vector<int>>& line_num){
    bool sum_zero = true;
    //std::cout<<"subset[i] "<< std::endl;
    int final_sum = 0;
    for (const auto& pair : Dealdeal){
        int sum = 0;
        int sum_prices = 0;
        for (int i = 0; i < subset.size(); i++){
            if(signals[subset[i]-1] == 'b'){
            sum -= pair.second[subset[i]-1];
            sum_prices -= prices[subset[i]-1];
            }
            if(signals[subset[i]-1] == 's'){
            sum += pair.second[subset[i]-1];
            sum_prices += prices[subset[i]-1];
            }
        }
        if( sum != 0 ) { sum_zero = false; break; }
        else{
            if( sum_prices >= 0){ sum_zero = false;}
        } 

        final_sum = sum_prices;
    }

    if(sum_zero){
        std::vector<std::string> line_line;
        std::vector<int> kimtan;
        for (int i = subset.size() - 1; i > -1; i--){
            line_line.push_back(all_lines[subset[i]-1]);
            kimtan.push_back(subset[i]-1);
            //std::cout<<subset[i] << std::endl;
        }
        arbitrage_lines.push_back(std::make_pair(line_line, final_sum));
        line_num.push_back(kimtan);

    }

}

void generate_valid_subsets(int n, int start, std::vector<int>& subset, std::vector<bool>& valid,const std::map<std::string, std::vector<int>>& Dealdeal,const std::vector<int>& prices,const std::vector<char>& signals,std::vector<std::string>& all_lines, std::vector<std::pair<std::vector<std::string>, int>>& arbitrage_lines, std::vector<std::vector<int>>& line_num) {
    // Base case: print the current subset if it contains n and all elements are valid
    //std::cout<<"subset[i] "<< std::endl;
    bool allValid = true;
    for (int i : subset) {
        if (!valid[i-1]) {
            allValid = false;
            break;
        }
    }
    if (find(subset.begin(), subset.end(), n) != subset.end() && allValid) {
        checkLinearCombo(subset, valid, Dealdeal, prices, signals, all_lines, arbitrage_lines, line_num);
    }

    // Recursive case: try adding each valid element from start to n to the subset
    for (int i = start; i <= n; i++) {
        // Skip if the element is not valid
        if (!valid[i-1]) continue;

        // Add i to the subset
        subset.push_back(i);

        // Recursively generate subsets with i + 1 as the new start
        generate_valid_subsets(n, i + 1, subset, valid, Dealdeal, prices, signals, all_lines, arbitrage_lines, line_num);

        // Remove i from the subset
        subset.pop_back();
    }
}

void make_structure(const std::string& message,std::map<std::string, std::vector<int>>& Dealdeal,int& currline, std::vector<int>& prices, std::vector<char>& signals, std::vector<bool>& validity, std::vector<std::string>& all_lines, std::vector<std::pair<std::vector<std::string>, int>>& arbitrage_lines, int& last_profit){
    std::string currentLine = "";
    for (char c : message) {
        if (c == '#') {
            currline++;
            order newOrder;
            all_lines.push_back(currentLine);
            // Create a string stream to process the line
            std::stringstream ss(currentLine);
            //std::cout<< currline << "\n";
            // Create a counter to keep track of the number of characters
            int count = 0;

            // Loop through the line and split it by space
            std::string word;
            while (ss >> word) {
                // Increment the counter
                count++;
            }

            std::stringstream iss(currentLine);

            std::string key;
            int value;
            for( int i = 0; i < count - 2 ; i++){
                iss >> key >> value;
                //std::cout<< key << " " << value << std::endl;
                auto it = Dealdeal.find(key);
                if (it == Dealdeal.end()){
                    for (int j = 0; j < currline; j++){
                        //std::cout << "Here" << std::endl;
                        Dealdeal[key].push_back(0); // if this is the fist time seeing the stock
                    }}
                Dealdeal[key].push_back(value);
                newOrder.stocks.push_back(key);
                i++;
            }


            for (auto it = Dealdeal.begin(); it != Dealdeal.end(); it++) {
            // Get the key from the map
            std::string key = it->first;

            
            if (find(newOrder.stocks.begin(), newOrder.stocks.end(), key) == newOrder.stocks.end()) {
                //std::cout << "Here" << std::endl;
                Dealdeal[key].push_back(0); // if the stocks were not present in this deal make them zero
            }
        }
            int new_price;
            char new_sign;
            iss >> new_price >> new_sign; // these are the data carried by each trade
            prices.push_back(new_price);
            signals.push_back(new_sign);
            validity.push_back(true);
            // our order data structure gets done here

            // Check i the order is valid or not means is it getting cancelled or not
            // Cancellation rules

            bool same_stocks = true;

                    for( int i = 0; i < prices.size() -1; i++){
                        same_stocks = true;
                        if(new_sign == 'b' && validity[i]){

                            // check if any linear combination is same
                            for (const auto& pair : Dealdeal){
                                if(pair.second[i] != Dealdeal[pair.first][currline]){
                                    same_stocks = false; break;
                                }
                            }
                            // if yes check for cancellation
                            if(same_stocks){
                                if( signals[i] == 's' && prices[i] == new_price){
                                    validity[i] = false; validity[currline] = false; std::cout<<"No Trade\n";
                                }
                                else if( signals[i] == 'b' && prices[i] > prices[currline]){
                                    validity[currline] = false; std::cout<<"No Trade\n";
                                }
                                else if( signals[i] == 'b' && prices[i] < prices[currline]){
                                    validity[i] = false; std::cout<<"No Trade\n";
                                }
                            }
                        }
                        else if(new_sign == 's' && validity[i]){

                             // check if any linear combination is same
                            for (const auto& pair : Dealdeal){
                                if(pair.second[i] != Dealdeal[pair.first][currline]){
                                    same_stocks = false; break;
                                }
                            }
                            // if yes check for cancellation
                            if(same_stocks){
                                if( signals[i] == 'b' && prices[i] == new_price){
                                    validity[i] = false; validity[currline] = false; std::cout<<"No Trade\n";
                                }
                                else if( signals[i] == 's' && prices[i] > prices[currline]){
                                    validity[currline] = false; std::cout<<"No Trade\n";
                                }
                                else if( signals[i] == 's' && prices[i] < prices[currline]){
                                    validity[i] = false;
                                    std::cout<<"No Trade\n";
                                }
                            }

                        }
                    }

                    //outputMap(Dealdeal);
                    std::vector<std::vector<int>> line_num;
                    std::vector<int> subset;

                    if( validity[currline]){
                        //std::cout<<"subset[i] "<< std::endl;
                        generate_valid_subsets(currline+1,1,subset,validity,Dealdeal, prices,signals, all_lines, arbitrage_lines, line_num);
                    }
                    if(!arbitrage_lines.empty()){
                        int max_profit = 0;
                        int index = 0;
                        for( int k =0; k < arbitrage_lines.size(); k++){
                            if(arbitrage_lines[k].second < max_profit){
                                max_profit = arbitrage_lines[k].second;
                                index = k;
                            }
                        }
                        for( int k = 0; k < arbitrage_lines[index].first.size(); k++){
                            std::string order_line = arbitrage_lines[index].first[k];
                            validity[line_num[index][k]] = false;
                            size_t pos=order_line.find_last_of(" ");
                            char current_signal=order_line[pos+1];
                            char new_signal=(current_signal== 'b') ? 's' : 'b';
                            order_line[pos+1]=new_signal;
                            std::cout<<order_line<<"\n";
                        }
                        last_profit -= max_profit;
                    }
                    else{
                        std::cout<<"No Trade\n";
                    }

                    arbitrage_lines.clear();
                    line_num.clear();

                    currentLine = "";
                    
        }
        else{
            currentLine += c;
        }
    }
}

void checkLinearCombo_part3(std::vector<int>& subset, std::vector<bool>& valid,const std::map<std::string, std::vector<int>>& Dealdeal,const std::vector<int>& prices,const std::vector<char>& signals,std::vector<std::string>& all_lines, std::vector<std::pair<std::vector<std::string>, int>>& arbitrage_lines, std::vector<int>& quantities, std::vector<std::vector<int>>& line_num){
    bool sum_zero = true;
    //std::cout<<"subset[i] "<< std::endl;
    int quant = 2147483600;
    int final_sum = 0;
    for (const auto& pair : Dealdeal){
        int sum = 0;
        int sum_prices = 0;
        for (int i = 0; i < subset.size(); i++){
            if(signals[subset[i]-1] == 'b'){
            sum -= pair.second[subset[i]-1];
            sum_prices -= prices[subset[i]-1];
            }
            if(signals[subset[i]-1] == 's'){
            sum += pair.second[subset[i]-1];
            sum_prices += prices[subset[i]-1];
            }
        }
        if( sum != 0 ) { sum_zero = false; break; }
        else{
            if( sum_prices >= 0){ sum_zero = false;}
        } 

        final_sum = sum_prices;
    }

    if(sum_zero){
        std::vector<std::string> line_line;
        std::vector<int> kimtan;
        for (int i = subset.size() - 1; i > -1; i--){
            line_line.push_back(all_lines[subset[i]-1]);
            kimtan.push_back(subset[i]-1);
            quant = std::min(quant, quantities[subset[i]-1]);
            //std::cout<<subset[i] << std::endl;
        }
        final_sum = final_sum*quant;
        arbitrage_lines.push_back(std::make_pair(line_line, final_sum));
        line_num.push_back(kimtan);

    }

}

void generate_valid_subsets_part3(int n, int start, std::vector<int>& subset, std::vector<bool>& valid,const std::map<std::string, std::vector<int>>& Dealdeal,const std::vector<int>& prices,const std::vector<char>& signals,std::vector<std::string>& all_lines, std::vector<std::pair<std::vector<std::string>, int>>& arbitrage_lines, std::vector<int>& quantities, std::vector<std::vector<int>>& line_num) {
    // Base case: print the current subset if it contains n and all elements are valid
    //std::cout<<"subset[i] "<< std::endl;
    bool allValid = true;
    for (int i : subset) {
        if (!valid[i-1]) {
            allValid = false;
            break;
        }
    }
    if (find(subset.begin(), subset.end(), n) != subset.end() && allValid) {
        //std::cout<<"subset[i] "<< std::endl;
        checkLinearCombo_part3(subset, valid, Dealdeal, prices, signals, all_lines, arbitrage_lines, quantities, line_num);
    }

    // Recursive case: try adding each valid element from start to n to the subset
    for (int i = start; i <= n; i++) {
        // Skip if the element is not valid
        if (!valid[i-1]) continue;

        // Add i to the subset
        subset.push_back(i);

        // Recursively generate subsets with i + 1 as the new start
        generate_valid_subsets_part3(n, i + 1, subset, valid, Dealdeal, prices, signals, all_lines, arbitrage_lines, quantities, line_num);

        // Remove i from the subset
        subset.pop_back();
    }
}

void make_structure_part3(const std::string& message,std::map<std::string, std::vector<int>>& Dealdeal,int& currline, std::vector<int>& prices, std::vector<char>& signals, std::vector<bool>& validity, std::vector<std::string>& all_lines, std::vector<std::pair<std::vector<std::string>, int>>& arbitrage_lines, int& last_profit, std::vector<int>& quantities){
    std::string currentLine = "";
    for (char c : message) {
        if (c == '#') {
            currline++;
            order newOrder;
            all_lines.push_back(currentLine);
            // Create a string stream to process the line
            std::stringstream ss(currentLine);
            //std::cout<< currline << "\n";
            // Create a counter to keep track of the number of characters
            int count = 0;

            // Loop through the line and split it by space
            std::string word;
            while (ss >> word) {
                // Increment the counter
                count++;
            }

            std::stringstream iss(currentLine);

            std::string key;
            int value;
            for( int i = 0; i < count - 3 ; i++){
                iss >> key >> value;
                //std::cout<< key << " " << value << std::endl;
                auto it = Dealdeal.find(key);
                if (it == Dealdeal.end()){
                    for (int j = 0; j < currline; j++){
                        //std::cout << "Here" << std::endl;
                        Dealdeal[key].push_back(0); // if this is the fist time seeing the stock
                    }}
                Dealdeal[key].push_back(value);
                newOrder.stocks.push_back(key);
                i++;
            }


            for (auto it = Dealdeal.begin(); it != Dealdeal.end(); it++) {
            // Get the key from the map
            std::string key = it->first;

            
            if (find(newOrder.stocks.begin(), newOrder.stocks.end(), key) == newOrder.stocks.end()) {
                //std::cout << "Here" << std::endl;
                Dealdeal[key].push_back(0); // if the stocks were not present in this deal make them zero
            }
        }
            int new_price;
            char new_sign;
            int new_quant;
            iss >> new_price >> new_quant >> new_sign; // these are the data carried by each trade
            //std::cout<< new_quant << std::endl;
            prices.push_back(new_price);
            signals.push_back(new_sign);
            if(new_quant != 0){
            validity.push_back(true);}
            else{
                validity.push_back(false);
            }
            quantities.push_back(new_quant);
            //std::cout<< new_quant << std::endl;
            // our order data structure gets done here

            // Check i the order is valid or not means is it getting cancelled or not
            // Cancellation rules

            bool same_stocks = true;

                    for( int i = 0; i < prices.size() -1; i++){
                        if( quantities[i] == 0 ){validity[i] = false; }
                        same_stocks = true;
                        //else{std::cout<<"subset[i] "<< std::endl;}
                        if(new_sign == 'b' && validity[i] && validity[currline]){

                            // check if any linear combination is same
                            for (const auto& pair : Dealdeal){
                                if(pair.second[i] != Dealdeal[pair.first][currline]){
                                    same_stocks = false; break;
                                }
                            }
                            // if yes check for cancellation
                            if(same_stocks){
                                if( signals[i] == 's' && prices[i] == new_price){
                                    if( quantities[i] == quantities[currline]){
                                        validity[i] = false; validity[currline] = false;}
                                    else if( quantities[i] > quantities[currline] ){
                                        validity[currline] = false;
                                        quantities[i] -= quantities[currline];
                                    }
                                    else if( quantities[i] < quantities[currline] ){
                                        validity[i] = false;
                                        quantities[currline] -= quantities[i];
                                    }
                                }
                            }
                        }
                        else if(new_sign == 's' && validity[i] && validity[currline]){

                             // check if any linear combination is same
                            for (const auto& pair : Dealdeal){
                                if(pair.second[i] != Dealdeal[pair.first][currline]){
                                    same_stocks = false; break;
                                }
                            }
                            // if yes check for cancellation
                            if(same_stocks){
                                if( signals[i] == 's' && prices[i] == new_price){
                                    if( quantities[i] == quantities[currline]){
                                        validity[i] = false; validity[currline] = false;}
                                    else if( quantities[i] > quantities[currline] ){
                                        validity[currline] = false;
                                        quantities[i] -= quantities[currline];
                                    }
                                    else if( quantities[i] < quantities[currline] ){
                                        validity[i] = false;
                                        quantities[currline] -= quantities[i];
                                    }
                                }
                            }

                        }
                    }

                    //outputMap(Dealdeal);

                    std::vector<int> subset;
                    std::vector<std::vector<int>> lin_sum;

                    if( validity[currline]){
                        //std::cout<<"subset[i] "<< std::endl;
                        generate_valid_subsets_part3(currline+1,1,subset,validity,Dealdeal, prices,signals, all_lines, arbitrage_lines,quantities, lin_sum);
                    }
                    if(!arbitrage_lines.empty()){
                        int max_profit = 0;
                        int index = 0;
                        for( int k =0; k < arbitrage_lines.size(); k++){
                            if(arbitrage_lines[k].second < max_profit){
                                max_profit = arbitrage_lines[k].second;
                                index = k;
                            }
                        }
                        int quantity = 2147483600; 
                        for( int k = 0; k < arbitrage_lines[index].first.size(); k++){
                            std::string order_line = arbitrage_lines[index].first[k];
                            quantity = std::min(quantity, quantities[lin_sum[index][k]]);}

                        last_profit -= max_profit;

                        for(int k = 0; k < arbitrage_lines[index].first.size(); k++){
                            quantities[lin_sum[index][k]] -= quantity;
                            std::string order_line = arbitrage_lines[index].first[k];
                            std::stringstream iss(order_line);
                            int count = 0;
                            std::string word;
                            while (iss >> word) {
                                // Increment the counter
                                count++;
                            }

                            std::stringstream ss(order_line);
                            for (int p = 0; p < count - 2; p++)
                            {   
                                ss >> word;
                                std::cout << word << " ";
                            }
                            

                            size_t pos=order_line.find_last_of(" ");
                            char current_signal=order_line[pos+1];
                            char new_signal=(current_signal== 'b') ? 's' : 'b';
                            order_line[pos+1]=new_signal;
                            std::cout << quantity << " " << new_signal << "\n";
                        }
                        
                    }
                    else{
                        std::cout<<"No Trade\n";
                    }

                    arbitrage_lines.clear();

                    currentLine = "";
                    
        }
        else{
            currentLine += c;
        }
    }
}
int main(int agrc,char* argv[]) {

    Receiver rcv;
    bool found_dollar=false;
    int partNumber=std::stoi(argv[1]);
    std::map<std::string, std::pair<int, char>> stock_lastord_buy;
    std::map<std::string, std::pair<int, char>> stock_lastord_sell;
    std::map<std::string, std::pair<int, char>> stock_lastord;

    std::vector<int> prices2;
       std::vector<char> signals2;
       std::vector<bool> validity2;
       std::vector<std::string> all_lines2;
       std::vector<std::pair<std::vector<std::string>, int>> arbitrage_lines2;
       int last_profit2 = 0;
       std::map<std::string, std::vector<int>> Dealdeal2;
       int currline2 = -1;


    std::vector<int> prices3;
            std::vector<int> quantities3;
            std::vector<char> signals3;
            std::vector<bool> validity3;
            std::vector<std::string> all_lines3;
            std::vector<std::pair<std::vector<std::string>, int>> arbitrage_lines3;
            int last_profit3 = 0;
            std::map<std::string, std::vector<int>> Dealdeal3;
            int currline3 = -1;

    while(!found_dollar){
        std::string message=rcv.readIML();
        if (message.find('$') != std::string::npos){
            if(partNumber==1){
                part1(message, stock_lastord, stock_lastord_buy, stock_lastord_sell);
            }
            if(partNumber==2){
                make_structure(message,Dealdeal2, currline2, prices2, signals2, validity2, all_lines2, arbitrage_lines2, last_profit2);
                std::cout<< last_profit2 << std::endl;}
            if(partNumber==3){
                make_structure_part3(message,Dealdeal3, currline3, prices3, signals3, validity3, all_lines3, arbitrage_lines3, last_profit3, quantities3);
                std::cout<< last_profit3 << std::endl;}
            rcv.terminate();
            found_dollar = true;
        }
        else{
        if(partNumber==1){
            part1(message, stock_lastord, stock_lastord_buy, stock_lastord_sell);
        }
        else if (partNumber==2){
            make_structure(message,Dealdeal2, currline2, prices2, signals2, validity2, all_lines2, arbitrage_lines2, last_profit2);
        }
        else if(partNumber==3){
            make_structure_part3(message,Dealdeal3, currline3, prices3, signals3, validity3, all_lines3, arbitrage_lines3, last_profit3, quantities3);}
        }
    }
    return 0;
}
