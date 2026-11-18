# Parking Lot Manager

*Cars in, cars out, fair charges.*

A console program in C for CSE115L (Programming Language I Lab), project 07. It manages a small parking lot: vehicles are parked, released and charged by the hour, and the day's earnings are tracked.

**Current version: V4** (menu loop, `switch` dispatch, input validation, classification rule as a selection ladder, counters and a running total).

## Build and run

```
gcc -Wall -Wextra -std=c89 -pedantic -o parking v4.c
./parking
```

The program compiles with no warnings and uses only `<stdio.h>`.

## Menu

| Option | Action |
|---|---|
| 1 | **Park a vehicle**: reads slot, vehicle number, vehicle type and minute in |
| 2 | **Release and charge**: reads minute out, prints a receipt, adds the charge to the day's total |
| 3 | **Show free slots**: draws the slot map (`[XX]` taken, `[nn]` free) and the free count |
| 4 | **Search by plate**: looks for a vehicle number in the lot |
| 5 | **Day's earnings**: vehicles parked, vehicles released, vehicles still inside, total and average |
| 6 | **Save & load**: explains that saving needs files (arrives in V5) |
| 0 | **Exit**: prints the final figures, and warns if a vehicle is still inside |

After a receipt, the program waits for **Enter** before showing the menu again.

## Charging rules

Billed hours are always rounded up using integer arithmetic only:

```
hours = (minutes + 59) / 60
```

This avoids the `minutes / 60 + 1` trap, which would charge two hours for exactly 60 minutes.

| Vehicle type | Rate per hour | Flat overnight cap |
|---|---|---|
| 1. Car | 30.00 taka | 200.00 taka |
| 2. Bike | 15.00 taka | 100.00 taka |
| 3. Bicycle | 5.00 taka | 30.00 taka |

Worked examples for a car (30 taka/hour):

| Minutes parked | Billed hours | Charge |
|---|---|---|
| 45 | 1 | 30.00 |
| 60 | 1 | 30.00 |
| 61 | 2 | 60.00 |
| 95 | 2 | 60.00 |
| 180 | 3 | 90.00 |

### Time and overnight stays

A "minute" is counted from **midnight of the day the vehicle arrived**: `0` is 00:00, `200` is 03:20, `1440` is midnight and `1500` is 01:00 the next day.

- Minute in must be from 0 to 1439.
- Minute out must be later than minute in, up to 2879 (the end of the following day).
- A stay is **overnight** when the minute out is 1440 or later. An overnight charge never exceeds the flat cap for that vehicle type.

## Input validation

Every entry is checked, and impossible values are rejected and asked for again:

| Field | Accepted |
|---|---|
| Menu choice | 0 to 6 |
| Slot number | 1 to 10 |
| Vehicle number | 1 to 9999 |
| Vehicle type | 1 to 3 |
| Minute in | 0 to 1439 |
| Minute out | later than minute in, up to 2879 |

Letters, decimals such as `3.5`, and entries with extra text such as `2 x` are all rejected. If the input stream ends, the program exits cleanly instead of looping.

## Sample session

```
Slot number (1-10)          e.g. 7   : 7
Vehicle number (1-9999)     e.g. 120 : 120
Vehicle type (1-3)         e.g. 2   : 1
Minute in (0-1439)         e.g. 200 : 200

Parked: vehicle 120 (Car) in slot 7 at minute 200.

Minute out (201-2879; 1440 = midnight) : 261

--------------- RECEIPT ----------------
  Slot no.       : 7
  Vehicle number : 120
  Vehicle type   : Car
  Minute in      : 200
  Minute out     : 261
  Time parked    : 61 min
  Billed hours   : 2 at 30.00 taka
  Charge         : 60.00 taka
----------------------------------------

Press Enter to continue...
```

## Code structure

`main` comes first, after the constants, global data and the function prototypes. Every other function is defined below it.

| Group | Functions |
|---|---|
| Screens | `Banner`, `Menu`, `show_receipt` |
| Input | `read_number`, `read_in_range`, `wait_for_enter` |
| Classification rules | `rate_for_type`, `cap_for_type` |
| Calculation | `calc_hours`, `calc_charge`, `apply_cap`, `is_overnight` |
| Menu actions | `park_vehicle`, `release_vehicle`, `show_free_slots`, `search_by_plate`, `show_earnings`, `save_and_load` |
| Helper | `print_type_name` |

The record being worked on (slot, vehicle number, type, minute in, minute out, charge) and the day's counters (vehicles parked, vehicles released, total earnings) are global variables.

## V4 requirements checklist

| Requirement | Where |
|---|---|
| Menu loop that runs until Exit | `do { ... } while (choice != 0)` in `main` |
| `switch` dispatch | `main`, and `print_type_name` |
| Input validation rejecting impossible values | `read_number`, `read_in_range`, and the checks in `park_vehicle` / `release_vehicle` |
| Classification rule as a selection ladder | `rate_for_type`, `cap_for_type` (`if / else if / else`) |
| Count and running total reported from the menu | `g_parked_count`, `g_released_count`, `g_earnings`, shown by option 5 |

## Limitations in this version

These come from what the course has covered so far, not from oversight:

- **The vehicle number is a whole number**, not a text plate. Strings arrive in V5.
- **The lot holds one vehicle at a time.** Arrays arrive in V5, so a second vehicle cannot be stored. Parking while a vehicle is inside is refused rather than overwriting it.
- **Search by plate** finds only the vehicle currently inside.
- **Nothing is saved.** The figures last until Exit. File saving arrives in V5.
- **The pause waits for Enter**, not any key, because standard C cannot read a single key press portably.

## Roadmap

| Version | Adds |
|---|---|
| V5 | Parallel arrays (with a text plate), add / search / sort / report, a function with an output parameter, save to and load from a text file |
| V6 | One array of `struct` in place of the parallel arrays, and one genuinely recursive function (first free slot from a given number) |

## Testing

`test_log_v4.txt` records the validation break attempts, the billing boundary cases (including exactly 60 minutes) and the overnight cap checks.
