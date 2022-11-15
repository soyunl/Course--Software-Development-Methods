#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
Created on Sat Jun 04 14:45:33 2022
@author: Soyun Lee

This is a file processor that allows to generate relevant statistics from F1 data.
"""

import sys
import pandas as pd
import matplotlib.pyplot as plt

def format_message(message: str) -> str:
    """Formats a message to be printed out to the standard output.

    Parameters
    ----------
    message : str, required
        The message to be printed out to the standard output.

    Returns
    -------
    str
        The formatted message.
    """
    return '[' + sys.argv[0] + ']: ' + message
    
def parse_filename(filename: str) -> list:
    filename = filename.split('=')
    parsed = filename[1].split(',')

    return parsed

def to_dataframe(filename: str) -> pd.DataFrame:
    df = pd.read_csv(filename)

    return df

def sort_winners(df: pd.DataFrame) -> pd.DataFrame:
    df_position = df.loc[df['positionOrder'] == 1]

    return df_position


def sort_keyword(list: pd.DataFrame,top: int,keyword: str) -> pd.DataFrame:
    counting = list[keyword].value_counts().head(top).reset_index(name='Counts')
    
    return counting

def get_name(list: pd.DataFrame, drivers: pd.DataFrame) -> pd.DataFrame:
    full_name = []
    for index,row in list.iterrows():
        driver_info = drivers.loc[drivers['driverId'] == row['index']]
        filtered_name = driver_info["forename"].values + ' ' + driver_info["surname"].values
        full_name.append(filtered_name)

    name = pd.DataFrame(full_name)
    list['index'] = name[0].values

    return list

def get_constructors(list: pd.DataFrame, constructors: pd.DataFrame) -> pd.DataFrame:
    list_constructors = []
    for index,row in list.iterrows():
        constructor_info = constructors.loc[constructors['constructorId'] == row['index']]
        filtered = constructor_info["name"].values
        list_constructors.append(filtered)

    constructor = pd.DataFrame(list_constructors)
    list['index'] = constructor[0].values
    
    return list


def by_nationality(list: pd.DataFrame, drivers: pd.DataFrame) -> pd.DataFrame:
    country_list = []
    for index,row in list.iterrows():
        driverId = row['driverId']
        driver_info = drivers.loc[drivers['driverId']==driverId]
        country_list.append(driver_info['nationality'].values)
    
    nationality = pd.DataFrame(country_list)
    counting = nationality[0].value_counts().head(10).reset_index(name='Counts')

    return counting

def sort_hosts(list: pd.DataFrame,circuits: pd.DataFrame) -> pd.DataFrame: #list=circuits.csv
    country_list = []
    for index,row in list.iterrows():
        circuitId = row['circuitId']
        country = circuits.loc[circuits['circuitId']==circuitId]
        country_list.append(country['country'].values)
    
    nationality = pd.DataFrame(country_list)
    counting = nationality[0].value_counts().head(20).reset_index(name='Counts')
    
    return counting

def sort_poles(df: pd.DataFrame) -> pd.DataFrame:
    df_pole = df.loc[df['grid'] != 1]
    return df_pole


def run_q1(drivers:pd.DataFrame,results:pd.DataFrame) -> pd.DataFrame:
    top = 20 #top 20 drivers
    keyword = 'driverId'
    top_list = sort_winners(results)
    by_name = sort_keyword(top_list,top,keyword)
    output = get_name(by_name,drivers)

    return output

def run_q2(drivers:pd.DataFrame,results:pd.DataFrame) -> pd.DataFrame:
    top = 10 #top 10 countries
    keyword = 'nationality'
    top_list = sort_winners(results)
    output = by_nationality(top_list,drivers)
    
    return output

def run_q3(constructors:pd.DataFrame,results:pd.DataFrame) -> pd.DataFrame:
    top = 10 #top 10 constructors
    keyword = 'constructorId'
    top_list = sort_winners(results)
    by_constructor = sort_keyword(top_list,top,keyword)
    output = get_constructors(by_constructor,constructors)

    return output

def run_q4(circuits:pd.DataFrame,races:pd.DataFrame) -> pd.DataFrame:
    top = 20 #top 20 host countries
    keyword = 'circuitId'
    output = sort_hosts(races,circuits)

    return output

def run_q5(drivers:pd.DataFrame,results:pd.DataFrame) -> pd.DataFrame:
    top = 5 #top 5 drivers
    keyword = 'driverId'
    top_list = sort_winners(results)
    non_pole = sort_poles(top_list)
    by_id = sort_keyword(non_pole,top,keyword)
    output = get_name(by_id,drivers)

    return output

def output_graph(df:pd.DataFrame,title:str,q:str):
    file_title = 'output_graph_q'
    x = list(df.iloc[:,0])
    y = list(df.iloc[:,1])
    plt.title(title)

    if (q=='1' or q=='4' or q=='5'):
        plt.xlabel('subject', fontsize=3)
        plt.ylabel('statistic')
        plt.xticks(rotation=75)
        plt.bar(x,y,color='r')
        plt.tight_layout()
    else:
        plt.pie(y, labels = x, autopct='%.1f%%')
        plt.ylabel('statistic')
    
    plt.savefig(file_title+q)


def main():
    """The main entry of the program.
    """
    # sample call to function
    print(format_message('running'))

    # TODO: Your code here.
    question = sys.argv[1]
    question = question[len('question')+3:]
    filename = sys.argv[2]
    input_combined = parse_filename(filename)
    input_1 = str(input_combined[0])
    input_2 = str(input_combined[1]) 
    df1 = to_dataframe(input_1)
    df2 = to_dataframe(input_2)

    if (question=='1'):
        result = run_q1(df1,df2)
        title = 'F1 race winners'
    elif (question=='2'):
        result = run_q2(df1,df2)
        title = 'F1 race winners by nationality'
    elif (question=='3'):
        result = run_q3(df1,df2)
        title = 'F1 race winners constructors'
    elif (question=='4'):
        result = run_q4(df1,df2)
        title = 'F1 race hosting countries'
    else:
        result = run_q5(df1,df2)
        title = 'F1 race winners with no pole position'

    result.columns = ['subject','statistic']
    output_graph(result,title,question)
    result.to_csv('output.csv',index=False)


if __name__ == '__main__':
    main()
