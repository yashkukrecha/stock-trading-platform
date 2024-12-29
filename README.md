# C++ Stock Trading Platform

A multithreaded, socket-based C++ stock trading platform. This project models real-time stock updates, order management, and client-server communication. Designed for extensibility and performance, the system incorporates modern C++ programming practices and testing using Google Test.

### Features
- **Stock Management:** Real-time stock price updates and price history tracking using Brownian motion.
- **Order Management:** Support for buy/sell orders with validation.
- **Multithreading:** Independent threads simulate real-time stock price updates.
- **Socket-Based Communication:** Traders connect to the server to place orders and query stocks.
- **Portfolio Optimization:** Risk toleration algorithm suggests the best stocks for the trader.
- **Unit Testing:** Verified using Google Test to ensure correctness and stability.

### Tech Stack
- **C++**
- **Google Test:** Unit Tests
- **Mutex:** Thread safety and synchronization
- **Pthread:** Multithreading support
- **Sockets:** TCP/IP Network Communication
- **CMake:** Build system generator
- **Valgrind:** Memory leak checker

### Running the Server
Clone the repository
```
git clone https://github.com/yashkukrecha/stock-trading-platform.git
cd stock-trading-platform/server
```

Create a ```build``` directory and configure the project (Note: the ```-DRUN_VALGRIND``` flag is optional)
```
mkdir build
cd build
cmake -DRUN_VALGRIND=ON ..
```

Build the project (Note: if you configured with the optional flag, use ```make valgrind```)
```
make
```

From the ```build``` directory, run the tests
```
./unit_tests
```

From the ```build``` directory, run the main method
```
./server
```

### Running the Client
Navigate to the client directory
```
cd stock-trading-platform/client
```

Create a ```build``` directory, configure the project, and run the main method
```
mkdir build
cd build
cmake ..
make
./client
```

You can now type messages into the terminal and trade your stocks!
```
GET_STOCKS
BUY:SYMBOL:QUANTITY (ex. BUY:AAPL:10)
SELL:SYMBOL:QUANTITY (ex. SELL:AAPL:10)
RECOMMEND:RISK_TOLERANCE:NUMBER_RECOMMENDATIONS (ex. RECOMMEND:1:4)
```