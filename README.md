# MCRC - Minecraft Recipe Calculator

**Important*** to note this was written on a MBP M1. Haven't tested it in other environments, so it may not work.

A C++ program that helps users calculate and manage crafting recipes with their precursor materials. Users can create, store, and calculate the required materials for crafting any item.

I made this program for a modpack called GregTech: New Horizons, because the recipes are brutal and the built-in crafting calculator isn't good enough

This is the first program I've written. There is no input validation. There are probably lots of bugs... sorry.

# Feautures
Recipe Management: Create and store crafting recipes in a JSON database

Dynamic & Recursive Recipe Creation: Add new recipes with their precursor materials. If a precursor doesn't exist, define it and add it to the database.

# Creation

```
What would you like to craft? (use "_" for spaces)
>iron_chest
Does it have any precursors? ('Y' or 'N')
>y
List precursors. (Use a ',' for separation and '_' for spaces)
>iron,chest
How many iron do you need?
>8
How many chest do you need?
>1
Recipe saved!
```
# Recall and Multiplication
```
What would you like to craft? (use "_" for spaces)
>iron_chest
Found iron_chest!
How many iron_chest would you like to craft?
>3
To make 3 iron_chest(s) you need:
24 iron
3 chest
24 wood
Continue? ('Y' or 'N')
```

# Firsts For Me

-Uses JSON for data storage and management


-Implements recursive algorithms for nested recipe calculations

-Random ID generation



# File Structure

main.cpp: Entry point and user interface

parseProc.h/cpp: Core recipe parsing and calculation logic

precursorToken.h: Data structure for precursor materials

recipes.json: Database file for storing recipes and base items

# Dependencies

nlohmann/json library for JSON handling

Standard Library




