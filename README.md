# Restaurant Management System

## Overview

This C++ project implements a restaurant management system for handling raw materials, menu items, clients, and orders. It includes file I/O (text and binary), exception handling, template classes, STL containers, and demonstrates OOP concepts such as inheritance, polymorphism, and operator overloading.

## Features

- Manage raw materials with nutritional information.
- Specialized vegan raw materials with allergen and certification details.
- Create and manage dishes composed of raw materials.
- Handle online and physical clients with specific attributes.
- Process orders including delivery orders (ComandaGlovo).
- Support text, binary, and CSV file formats.
- Generate reports on stock, pricing, calories, revenue, and client preferences.
- Use template classes and STL containers (vector, list, set, map).
- Custom exception handling.
- Operator overloading for intuitive usage.
- Virtual functions for polymorphic file operations.

## Classes

- `MateriePrima` / `MateriePrimaVegana`: Represent raw materials.
- `Preparat`: Represents dishes made from raw materials.
- `Client`: Represents customers (online or physical).
- `Comanda` / `ComandaGlovo`: Represents orders, including delivery orders.
- `MeniuRestaurant`: Contains pointers to dishes available in the menu.
- `Producator<T>`: Template class for producers managing elements of any type.
- `Exceptie`: Custom exception class.

## How to Use

1. Compile with a C++11 (or newer) compatible compiler.
2. Run the executable.
3. Use the menu to manage materials, dishes, clients, and orders.
4. Generate reports or save/load data from files.

## File Formats

- `.txt` (text)
- `.bin` (binary)
- `.csv`

## Dependencies

Standard C++ libraries only.

