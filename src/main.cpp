#include "market.h"

using namespace std;

mutex stock_mutex;
volatile bool running = true;

void signal_handler(int signal) {
    if (signal == SIGINT) {
        cout << "\nShutting down the market simulation...\n";
        running = false;
    }
}

void *stock_function (void* arg) {
    Stock *stock_ptr = static_cast<Stock*>(arg);
    while (running) {
        stock_ptr->brownian_motion();

        // print the stock safely
        stock_mutex.lock();
        stock_ptr->print_stock();
        stock_mutex.unlock();

        // sleep for 5 seconds
        sleep(5);
    }
    return nullptr;
}

int main () {

    signal(SIGINT, signal_handler);

    Market market;

    Stock apple("AAPL", "Apple Inc.", 259.28);
    Stock tesla("TSLA", "Tesla Inc.", 454.13);
    Stock amazon("AMZN", "Amazon.com Inc.", 227.62);
    Stock google("GOOG", "Alphabet Inc. Class C", 197.48);
    Stock microsoft("MSFT", "Microsoft Corp.", 438.94);

    market.add_stock(apple, 1000);
    market.add_stock(tesla, 1000);
    market.add_stock(amazon, 1000);
    market.add_stock(google, 1000);
    market.add_stock(microsoft, 1000);

    pthread_t apple_thread, tesla_thread, amazon_thread, google_thread, microsoft_thread;
    pthread_create(&apple_thread, nullptr, stock_function, &apple);
    pthread_create(&tesla_thread, nullptr, stock_function, &tesla);
    pthread_create(&amazon_thread, nullptr, stock_function, &amazon);
    pthread_create(&google_thread, nullptr, stock_function, &google);
    pthread_create(&microsoft_thread, nullptr, stock_function, &microsoft);

    pthread_join(apple_thread, nullptr);
    pthread_join(tesla_thread, nullptr);
    pthread_join(amazon_thread, nullptr);
    pthread_join(google_thread, nullptr);
    pthread_join(microsoft_thread, nullptr);

    return 0;
}