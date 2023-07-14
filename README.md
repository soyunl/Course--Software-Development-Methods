# Course--Software-Development-Methods
Completed projects from Software Development Methods course. Further information about the course can be found [here](https://heat.csc.uvic.ca/coview/course/2022051/SENG265)

<h2>Projects</h2>
---
<h3>A1: icalendar Scheduler</h3>
Program written in C that inputes lines of data from a provided calendar file (.ics), accepts options and arguments from the command line, and then outputs to the console events from the calendar file into a more readable format. 

```bash
# input
./event_manager --start=2022/2/14 --end=2022/2/14 --file=one.ics
```
```bash
# output
February 14, 2021 
------------------------
6:00 PM to 9:00 PM: Romantic dinner with Chris {{Burger king}
```
```bash
# test
./event_manager --start=2022/2/1 --end=2022/3/1 --file=diana-devops.ics | diff test02.txt -
```

<h3>A2: Data Analysis on F1</h3>
Program written in Python that uses relevant Python structures and libraries to process historical F1 data to produce descriptive analytics. Based on provided arguments and data files, the program focused on answering the following questions: 

1. Top 20 drivers with most wins in F1 history
2. Top 10 countries with most race-winners in F1 history
3. Top 10 constructors with most wins in F1
4. Top 20 countries with most hosted F1 races?
5. Top 5 drivers with most wins in F1 history who started a race not in pole position

The program generates two output files:
- A CSV file containing the results of the analysis in a table-based format
- A PNG file containing a bar chart of the results of the analysis
```bash
# input
./f1_statistics.py --question=1 --files=drivers.csv,results.csv
```

<h3>A3: Data Analysis on Songs</h3>
Program written in C that uses memory allocation and dynamic data structures to process a large dataset of songs to produce descriptive analytics. Based on provided arguments and data files, the program focused on answering the following questions:

1. Top 10 songs released in 1999 with most popularity score
2. Top 5 songs released in 1999 with most energy score
3. Top 3 songs released in 1999 with most danceability score
4. Top 3 songs released in 2009 with most popularity score
5. Top 5 songs released in 2019 with most danceability score
6. Top 5 songs released in 1999 *or* 2009 with most energy score
7. Top 10 songs released in 1999, 2009, *or* 2019 with most popularity score

The program generates an output file that contains four demensional data with the following columns: Artist, Song, Year, and Category. 

<h3>A4: Card Generator</h3>
Program written in Python that uses customized classes to generate greeting cards in the form of HTML-SVG pages. [Example]() of a generated card.
