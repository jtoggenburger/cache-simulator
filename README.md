# cache-simulator
A program which simulates a cache with various eviction policies in C

## Building

Build this program with:
```
make
```
or
```
make all
```

## Execution

Initialize the cache simulator:
```
$ ./cacher [-N cache size] <policy>
```

The following are the various policies that may be selected:
--F : First in First Out
--L : Least Recently Used
--C : Clock policy


## Usage

Start cacher with a fixed cache size and policy, then send any newline seperated item to it via stdin. cacher will report if the item was a HIT or MISS after recieving each item. At the end of execution, cacher will print out the number of capacity missses and compulsory misses.
