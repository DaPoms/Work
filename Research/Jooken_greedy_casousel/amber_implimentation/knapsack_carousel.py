#This was not made by me, it was made by Kulp, Amber at Kutztown university. I am just analyzing this program to make sure my C++ version has a similar behavior (or pointing out possible changes)
#!/usr/bin/env python
import math
import random
from pathlib import Path
import csv
import os
from tqdm import tqdm
import time
import numpy as np 

def readWord(fptr):
    word = ""
    while True:
        char = fptr.read(1)
        if (char == " " or char == "\n"):
            if word == "":
                continue
            else: break
        if char == '':
            return -1
        word += char
    return word

def readTXT(filename):
    with open(filename, 'r') as fptr:
        numItems = int(readWord(fptr))
        counter = 0
        itemsDictionary = {}
        while counter < numItems:
            item = int(readWord(fptr))
            profit = int(readWord(fptr))
            weight = int(readWord(fptr))
            itemsDictionary[item] = (profit, weight)
            counter += 1
        capacity = int(readWord(fptr))
    return itemsDictionary, capacity, numItems

def removeItem(selectedItems, weight, totalWeight, profit, profits, item):
    totalWeight -= weight
    selectedItems.pop(item)
    profits -= profit
    return selectedItems, totalWeight, profits

def greedyHeuristic(selectedItems, itemDictionary, capacity, total_weight=0, profits=0):
    # Sort items by profit/weight ratio
    remainingItems = {k: v for k, v in itemDictionary.items() if k not in selectedItems}
    sortedRemaining = dict(sorted(remainingItems.items(), key=lambda x: (x[1][0] / x[1][1]), reverse=True))
    for item in sortedRemaining:
        stuff = sortedRemaining[item]
        profit, weight = stuff
        if total_weight + weight <= capacity:
            selectedItems, total_weight, profits = addItem(selectedItems, weight, total_weight, profit, profits, item)
    return selectedItems, total_weight, profits

def addItem(selectedItems, weight, weights, profit, profits, item):
    weights += weight
    profits += profit
    selectedItems[item] = (profit, weight)
    return selectedItems, weights, profits

def improvement(selectedItems, itemDictionary, capacity, totalWeight, profits):
    reversedSelected = dict(reversed(list(selectedItems.items())))
    remainingItems = {k: v for k, v in itemDictionary.items() if k not in selectedItems}
    sortedRemaining = dict(sorted(remainingItems.items(), key=lambda x: (x[1][0] / x[1][1]), reverse=True))
    for item in reversedSelected:
        potentialWeight = 0
        potentialProfits = 0
        potentialItems = {}
        profit, weight = reversedSelected[item]

        for newItem in sortedRemaining:
            newProfit, newWeight = sortedRemaining[newItem]
            if newWeight + potentialWeight < weight: #case never reached
                potentialItems[newItem] = (newProfit, newWeight) 
                potentialWeight += newWeight
                potentialProfits += newProfit

        if potentialProfits > profit:
            print("Updating") ##case never reached
            reversedSelected, totalWeight, profits = removeItem(reversedSelected, weight, totalWeight, profit, profits, item)
            # Add the item removed into the remaining items and re-sort
            sortedRemaining.push(item, (profit, weight))
            sortedRemaining = dict(sortedRemaining.items(), key=lambda x: (x[1][0] / x[1][1]), reverse=True)

            for newItem in potentialItems:
                newProfit, newWeight = potentialItems[newItem]
                reversedSelected, totalWeight, profits = addItem(reversedSelected, newWeight, totalWeight, newProfit, profits, newItem)
                sortedRemaining.pop(newItem)

    for item in sortedRemaining:  
        newProfit, newWeight = sortedRemaining[item]
        if totalWeight + newWeight <= capacity:
            reversedSelected, totalWeight, profits = addItem(reversedSelected, newWeight, totalWeight, newProfit, profits, item)

    return reversedSelected, totalWeight, profits
            
def addOneGreedy(selectedItems, sortedRemaining, capacity, totalWeight, profits):
    #remainingItems = {k: v for k, v in itemDictionary.items() if k not in selectedItems}
    #sortedRemaining = dict(sorted(remainingItems.items(), key=lambda x: (x[1][0] / x[1][1]), reverse=True))
    for item in sortedRemaining:
        profit, weight = sortedRemaining[item]
        if totalWeight + weight <= capacity:
            selectedItems, totalWeight, profits = addItem(selectedItems, weight, totalWeight, profit, profits, item)
            break
    return selectedItems, totalWeight, profits

def carouselGreedy(InitialSelectedItems, capacity, itemDictionary, totalWeight, profits, a, b):
    remainingItems = {k: v for k, v in itemDictionary.items() if k not in InitialSelectedItems}
    #sortedRemaining = dict(sorted(remainingItems.items(), key=lambda x: (x[1][0] / x[1][1]), reverse=True))
    
    percentageToRemove = int(InitialSelectedItems.keys().__len__() * b)
    selectedItems = dict(list(InitialSelectedItems.items())[percentageToRemove:])
    removedItems = list(InitialSelectedItems.items())[:percentageToRemove]
    for item in removedItems:
        profit, weight = item[1]
        totalWeight -= weight
        profits -= profit
    
    carouselCounter = 0
    while carouselCounter < a:
        # Remove one item from selected items and update everything
        item, stuff = selectedItems.popitem()
        profit, weight = stuff
        totalWeight -= weight
        profits -= profit
        #sortedRemaining = dict(sorted(remainingItems.items(), key=lambda x: (x[1][0] / x[1][1]), reverse=True))
        selectedItems, totalWeight, profits = addOneGreedy(selectedItems, remainingItems, capacity, totalWeight, profits) #Issue??? should initialselectedItems = selectedItems
        carouselCounter += 1
    weightChecker = 0
    for object in selectedItems:
        weightChecker += itemsDictionary[object][1]
    if weightChecker != totalWeight:
        print("BADDDD!")
        exit()
    selectedItems, totalWeight, profits = greedyHeuristic(selectedItems, itemDictionary, capacity, totalWeight, profits) #fills in possible gaps?
    
    return selectedItems, totalWeight, profits


def writeToCSV(filename, matrix, headers, directory, greedyItemsProfitsList, greedyTimesList):
    csvFile = open(filename, "w", newline='')
    finalMatrix = np.array(matrix)
    writer = csv.writer(csvFile)
    writer.writerow(headers)
    rowCounter = 0
    columnCounter = 0
    for root, dirs, files in os.walk(directory):
        for dir in (dirs):
            columnCounter = 0
            row = [dir, greedyItemsProfitsList[dir], greedyTimesList[dir]]
            while columnCounter < finalMatrix.shape[0]:
                row.append(finalMatrix[columnCounter][rowCounter][0])
                row.append(finalMatrix[columnCounter][rowCounter][1])
                columnCounter += 1
            writer.writerow(row)
            rowCounter += 1
    csvFile.close()

if __name__ == '__main__':
    
    # csvFile = open("knapsack_carousel_b=", str(b), ".csv", "w", newline='')
    # writer = csv.writer(csvFile)
    headers = ['File', 'Greedy w/ Improvement (GI) Obj', 'Greedy w/ Improvement Time']


    a = 6
    b = 0.1
    finalMatrix = []
    directory = Path("C:/Users/Pomer/projects/Research/Jooken_greedy_casousel/problemInstances") #change to folder you want to explore the models of
    selectedItems = {}
    #totalWeight = 0
    profits = 0
    greedyItemsList = {}
    greedyTimesList = {}
    greedyItemsProfitsList = {}
    greedyWeightsList = {}
    profitsList = []
    timeList = []
    # Holds all the rows for 1 a value
    rowList = []
    while b <= 0.5:
        a = 6
        rowList
        while a <= 30:
            headers.append('Greedy w/ Improvement (GI) a=' + str(a) + ' Obj')
            headers.append('Greedy w/ Improvement Time a=' + str(a))
            for root, dirs, files in os.walk(directory):
                for dir in tqdm(dirs):
                    # print("Processing:", dir)
                    inputFile = os.path.join(root, dir, 'test.in')
                    startTime = time.time()
                    with open(inputFile, 'r') as fptr:
                        itemsDictionary, capacity, numItems = readTXT(inputFile)
                    # Only do this once, the no carousel case (which we feed into the carousel)
                    if a == 6 and b == 0.1:
                        selectedItems = {}
                        greedyItems, greedyWeight, greedyProfits = greedyHeuristic(selectedItems, itemsDictionary, capacity)
                        # greedyTime = time.time() - startTime
                        greedyItems, greedyWeight, greedyProfits = improvement(selectedItems, itemsDictionary, capacity, greedyWeight, greedyProfits)
                            #greedyItems, greedyWeight, greedyProfits = improvement(selectedItems, itemsDictionary, capacity, totalWeight, profits)
                        improvedTime = time.time() - startTime
                        # finalObjectives.append(greedyProfits)
                        greedyTimesList[dir] = improvedTime
                        greedyItemsList[dir] = greedyItems
                        greedyItemsProfitsList[dir] = greedyProfits
                        greedyWeightsList[dir] = greedyWeight
                    # carouselSelectedItems, carouselTotalWeights, carouselProfits = carouselGreedy(greedySelectedItems, capacity, itemsDictionary, greedyTotalWeights, greedyProfits, a, b)
                    # carouselTime = time.time() - startTime
                    # carouselSelectedItemsImproved, carouselTotalWeightsImproved, carouselProfitsImproved = improvement(carouselSelectedItems, itemsDictionary, capacity, carouselTotalWeights, carouselProfits)
                    # improvedCarouselTime = time.time() - startTime
                    
                    # weightChecker = 0
                    # for object in selectedItems:
                    #     weightChecker += itemsDictionary[object][1]
                    # if weightChecker != greedyWeight:
                    #     print("BADDDD!")
                    #     exit()

                    carouselSelectedItemsGI, carouselTotalWeightsGI, carouselProfitsGI = carouselGreedy(greedyItemsList[dir], capacity, itemsDictionary, greedyWeightsList[dir], greedyItemsProfitsList[dir], a, b)
                    # improvedCarouselTimeGI = time.time() - startTime
                    weightChecker = 0
                    for object in carouselSelectedItemsGI:
                        weightChecker += itemsDictionary[object][1]
                    if weightChecker != carouselTotalWeightsGI:
                        print("BADDDD!")
                        exit()

                    carouselSelectedItemsGIImproved, carouselTotalWeightsGIImproved, carouselProfitsGIImproved = improvement(carouselSelectedItemsGI, itemsDictionary, capacity, carouselTotalWeightsGI, carouselProfitsGI)
                    improvedCarouselTimeGIImproved = time.time() - startTime
                    rowList.append((carouselProfitsGIImproved, improvedCarouselTimeGIImproved))
            a += 6
            finalMatrix.append(rowList)
        writeToCSV("knapsack_carousel_b=" + str(b) + ".csv", finalMatrix, headers, directory, greedyItemsProfitsList, greedyTimesList)
        b += 0.1
        
