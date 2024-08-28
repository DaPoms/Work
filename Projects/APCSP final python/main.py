import random
import os

#Var initialize######################
Trans = ""
End = 0
#####################################





#########Pool(64 terms)########################
#You can edit these terms to change what you are studying! Ex: List animals in one list, and their kingdom in the second one! Make sure each answer and question is different though
# IMPORTANT: Make sure to keep track of the amount of terms you have in the list, and then SUBTRACT it by 1 (as python lists start at 0, not 1) The length of your list is then put in the call function as shown in the procedure itself. MAKE SURE both lists have equal length.
SPpool = [
    "Cuadro", "Hogar", "Aire Acondicionado", "Alfombra", "Armario", "Ático",
    "Bombilla", "Cerca", "Chimenea", "Cortadora de Césped", "Cortina",
    "Despertador", "Escoba", "Ladrillo", "Lavadora", "Madera", "Mueble",
    "Muro", "Reja", "Secadora", "Sillón", "Sótano", "Techo", "Ventilador",
    "Cómoda", "Estante", "Mesa de Noche", "Percha", "Sofá", "Suelo",
    "Almohada", "Cobija", "Colchón", "Cubrecama", "Funda", "Sábana", "Cambiar",
    "Cortar", "Dejar", "Encargarse", "Exagerar", "Ganar", "Insistir",
    "Invitar", "Bisabuelo/Bisabuela", "Hermanastro / Hermanastra", "Mamá",
    "Miembro", "Padastro / Madastra", "Papá", "Abajo", "Adentro", "Afuera",
    "Arriba", "Beso", "Broma", "Cuidado", "Premio", "Tener Cuidado", "Puro/a",
    "Pájaro", "Mascota", "Horno", "Microondas"
]



ENGpool = [
    "Picture", "Home", "Air Conditioning", "Rug", "Wardrobe", "Attic",
    "Light Bulb", "Fence", "Chimney", "Lawn Mower", "Curtain", "Alarm Clock",
    "Broom", "Brick", "Washer", "Wood", "Furniture", "Wall",
    "Iron Fence / Window Grille", "Dryer", "Arm Chair", "Basement", "Roof",
    "Fan", "Dresser / Bureau", "Shelving / Bookcase", "Night Table/ Stand",
    "Hanger", "Sofa", "Floor", "Pillow", "Blanket", "Mattress",
    "Comforter / Bedcover", "Pillowcase", "Sheet", "To Change", "To Cut",
    "To Let / Allow", "To make responsible for / take care of",
    "To Exaggerate", "To win / Earn", "To Insist", "To Invite",
    "Great-Grandfather/Grandmother", "Stepbrother / Stepsister", "Mom",
    "Member", "Stepfather / Stepmother", "Dad", "Downstairs / Down", "Inside",
    "Outside", "Upstairs / Above / Up", "Kiss", "Joke", "Care", "Prize",
    "To be Careful", "Pure / Fresh", "Bird", "Pet", "Oven", "Microwave"
]





###### Def / procedure ###################### 
#Give the 2 lists and what you want to translate to (This can be edited to work with things other than language, see comment down bellow at line 96)
def scramble(list1, list2, transLang):
    listTotal = len(list1) 
    
    pointX = 1
    pointGain = 1
    pointTotal = 0
    streak = 0
    streakinc = 1
    combo = 0
  #The problem list is to form the format of each question (there are 4 possible answers). Increment just increments by 1, to make sure the ranindex list gets fully sweeped through
    lives = 5
    increment = 0
    problem = [0, 0, 0, 0]
    
    # Creates a list of random numbers from the length of the study terms
    ranindex = random.sample(range(listTotal), listTotal)

    
     #Program runs on lives
    while lives != 0:
  
      #Answers are determined using the index given in the ranindex list. The indexes of the pool section are answers to eachother (EX: ENGpool[0] = Picture and SPpool[0] = Cuadro)
        ans = ranindex[increment] 
      #The order list is used to randomize the problem list, and we know that when we do problem[order[0]], we will always be showing the answer to the problem.
        order = random.sample(range(4),4)
  
        problem[order[0]] = list2[ans]
      
        problem[order[1]] = list2[random.randint(0,63)]
        problem[order[2]] = list2[random.randint(0,63)]
        problem[order[3]] = list2[random.randint(0,63)]
# This is used to make sure there are not repeats, as if there are repeats, the SET of a list will be shorter than the normal 4 length.
        while len(set(problem)) != len(problem):
          problem[order[1]] = list2[random.randint(0,63)]
          problem[order[2]] = list2[random.randint(0,63)]
          problem[order[3]] = list2[random.randint(0,63)]
        
          #This asks the question, with answer being put in input Ans variable. You can edit this sentence to make it work for things other than language translation.
        inputAns = str(input("-------------\nWhat is \033[4;1;94m" + list1[ans] + "\033[0m in " + transLang + "? \n A: " + problem[0] + "\n B: " + problem[1] + "\n C: " + problem[2] + "\n D: " + problem[3] + "\n\n E: \033[31;1;38mGo to shop\033[0m" + "\n-------------\n You say: "))
        os.system('cls')
      #I put a few of these statements, where I ask for an input, and then have a while statement that repeats the question if you input an answer that is not accepted.
      
        while inputAns != "A" and inputAns != "a" and inputAns != "B" and inputAns != "b" and inputAns != "C" and inputAns != "c" and inputAns != "D" and inputAns != "d" and inputAns != "E" and inputAns != "e":
            os.system('cls')        
            print("-------------\nInvalid Input, try again")
            
            
            inputAns = input("-------------\nWhat is \033[4;1;94m" + list1[ans] + "\033[0m in " + transLang + "? \n A: " + problem[0] + "\n B: " + problem[1] + "\n C: " + problem[2] + "\n D: " + problem[3] + "\n\n E: \033[31;1;38mGo to shop\033[0m" + "\n-------------\n You say: ")
          #The os.system('cls') is for aesthetic purposes, clss the screen for every user input.
        os.system('cls')
#User input for the answer
        if inputAns == "A" or inputAns == "a":
            inputAns = 0
            
        elif inputAns == "B" or inputAns == "b":
            inputAns = 1
  
        elif inputAns == "C" or inputAns == "c":
            inputAns = 2
##############Shop##################################
      #E or e is for the shop. The shop is the main bulk / inefficient part of the code. In this there are 3 factors: 1.Base point increase 2. Streak bonus 3. Money multiplier. This code is mainly inefficient as each type of factor could be made into another procedure, but I realized that I had integrated these variables for too long, so trying to get these variables to work in another internal procedure was not worth it. Each item costs points aquired from getting answers right. PLUS, there is no reason for the shop to be MODULAR, as the shop is something that is permanent, that doesn't ever really need to change.
        elif inputAns == "E" or inputAns == "e":
         
          os.system('cls')
          shopAns = input("-------------\nChose what you want to upgrade:\n A: Base Income \n B: Streak Bonus \n C: Money Multiplier \n D: Exit \n-------------\nYou say:")
        #Split into A,B,C, and D. A is Base income, B is Streak bonus, C is Money multiplier, and D to exit.
          if shopAns == "A" or shopAns == "a":
            os.system('cls')
            
            upgrade = input("-------------\nBase Income\n-------------\nCurrent money: $" + str(pointTotal) + "\n\n 1. $5 income (Price: $10) \n 2. $50 income (Price: $100) \n 3. $100 income (Price: $1,000) \n 4. $500 income (Price: $10,000) \n 5. $2,000 income (Price: $75,000) \n 6. $5,000 income (Price: $300,000) \n 7. $10,000 income (Price: $1,000,000) \n 8. $250,000 income (Price: $10,000,000) \n\n 9. Exit \n-------------\n You say: ")


            while upgrade != "1" and upgrade != "2" and upgrade != "3" and upgrade != "4" and upgrade != "5" and upgrade != "6" and upgrade != "7" and upgrade != "8" and upgrade != "9":
              os.system('cls')
              print("-------------\nInvalid")
              upgrade = input("-------------\nBase Income\n-------------\nCurrent money: $" + str(pointTotal) + "\n\n 1. $5 income (Price: $10) \n 2. $50 income (Price: $100) \n 3. $100 income (Price: $1,000) \n 4. $500 income (Price: $10,000) \n 5. $2,000 income (Price: $75,000) \n 6. $5,000 income (Price: $300,000) \n 7. $10,000 income (Price: $1,000,000) \n 8. $250,000 income (Price: $10,000,000) \n\n 9. Exit \n-------------\n You say: ")
              
             
            
              #Streak is reset upon upgrading, and there is a limiter set in place to prevent users from buying the same item more than once, and also buying it without enough points
            if upgrade == "1" :
              if pointTotal >= 10 and pointGain < 5:
                pointGain = 5
                pointTotal = pointTotal - 10
                os.system('cls')
                print("-------------\nYou now gain $" + str(pointGain) + " per question!")
                streak = 0
                
              elif pointTotal < 10:   
                os.system('cls')              
                print("-------------\nYou do not have enough money!")
                              
              else:
                os.system('cls')
                print("-------------\nYou have already purchased this!")
              continue
              
            elif upgrade == "2" :
              if pointTotal >= 100 and pointGain < 50:
                pointGain = 50
                pointTotal = pointTotal - 100
                os.system('cls')
                print("-------------\nYou now gain $" + str(pointGain) + " per question!")
                streak = 0
                
              elif pointTotal < 100:   
                os.system('cls')              
                print("-------------\nYou do not have enough money!")
                              
              else:
                os.system('cls')
                print("-------------\nYou have already purchased this!")
              continue

            elif upgrade == "3" :
              if pointTotal >= 1000 and pointGain < 100:
                pointGain = 100
                pointTotal = pointTotal - 1000
                os.system('cls')
                print("-------------\nYou now gain $" + str(pointGain) + " per question!")
                streak = 0
                
              elif pointTotal < 1000:   
                os.system('cls')              
                print("-------------\nYou do not have enough money!")
                              
              else:
                os.system('cls')
                print("-------------\nYou have already purchased this!")
              continue

            elif upgrade == "4" :
              if pointTotal >= 10000 and pointGain < 500:
                pointGain = 500
                pointTotal = pointTotal - 10000
                os.system('cls')
                print("-------------\nYou now gain $" + str(pointGain) + " per question!")
                streak = 0
                
              elif pointTotal < 10000:   
                os.system('cls')              
                print("-------------\nYou do not have enough money!")
                              
              else:
                os.system('cls')
                print("-------------\nYou have already purchased this!")
              continue

            elif upgrade == "5" :
              if pointTotal >= 75000 and pointGain < 2000:
                pointGain = 2000
                pointTotal = pointTotal - 75000
                os.system('cls')
                print("-------------\nYou now gain $" + str(pointGain) + " per question!")
                streak = 0
                
              elif pointTotal < 75000:   
                os.system('cls')              
                print("-------------\nYou do not have enough money!")
                              
              else:
                os.system('cls')
                print("-------------\nYou have already purchased this!")
              continue

            elif upgrade == "6" :
              if pointTotal >= 300000 and pointGain < 5000:
                pointGain = 5000
                pointTotal = pointTotal - 300000
                os.system('cls')
                print("-------------\nYou now gain $" + str(pointGain) + " per question!")
                streak = 0
                
              elif pointTotal < 300000:   
                os.system('cls')              
                print("-------------\nYou do not have enough money!")
                              
              else:
                os.system('cls')
                print("-------------\nYou have already purchased this!")
              continue

            elif upgrade == "7" :
              if pointTotal >= 1000000 and pointGain < 10000:
                pointGain = 10000
                pointTotal = pointTotal - 1000000
                os.system('cls')
                print("-------------\nYou now gain $" + str(pointGain) + " per question!")
                streak = 0
                
              elif pointTotal < 1000000:   
                os.system('cls')              
                print("-------------\nYou do not have enough money!")
                              
              else:
                os.system('cls')
                print("-------------\nYou have already purchased this!")
              continue

            elif upgrade == "8" :
              if pointTotal >= 10000000 and pointGain < 250000:
                pointGain = 250000
                pointTotal = pointTotal - 10000000
                os.system('cls')
                print("-------------\nYou now gain $" + str(pointGain) + " per question!")
                streak = 0
                
              elif pointTotal < 10000000:   
                os.system('cls')              
                print("-------------\nYou do not have enough money!")
                              
              else:
                os.system('cls')
                print("-------------\nYou have already purchased this!")
              continue
              

            else:
              os.system('cls')
              continue

          if shopAns == "B" or shopAns == "b":
           
            os.system('cls')
            upgrade = input("-------------\nStreak Bonus\n-------------\n Current money: $" + str(pointTotal) + "\n\n 1. $3 streak bonus (Price: $20) \n 2. $10 streak bonus (Price: $200) \n 3. $50 streak bonus (Price: $2,000) \n 4. $250 streak bonus (Price: $20,000) \n 5. $1,200 streak bonus (Price: $200,000) \n 6. $6,500 streak bonus (Price: $2,000,000) \n 7. $35,000 streak bonus (Price: $20,000,000) \n 8. 175,000 streak bonus (Price: $200,000,000) \n\n 9. Exit \n-------------\n You say: ")

            while upgrade != "1" and upgrade != "2" and upgrade != "3" and upgrade != "4" and upgrade != "5" and upgrade != "6" and upgrade != "7" and upgrade != "8" and upgrade != "9":
             
              os.system('cls')
              print("-------------\nInvalid")
              upgrade = input("-------------\nStreak Bonus\n-------------\n Current money: $" + str(pointTotal) + "\n\n 1. $3 streak bonus (Price: $20) \n 2. $10 streak bonus (Price: $200) \n 3. $50 streak bonus (Price: $2,000) \n 4. $250 streak bonus (Price: $20,000) \n 5. $1,200 streak bonus (Price: $200,000) \n 6. $6,500 streak bonus (Price: $2,000,000) \n 7. $35,000 streak bonus (Price: $20,000,000) \n 8. $175,000 streak bonus (Price: $200,000,000) \n\n 9. Exit \n-------------\n You say: ")
              
            if upgrade == "1" :
              if pointTotal >= 20 and streakinc < 3:
                streakinc = 3
                pointTotal = pointTotal - 20
                os.system('cls')
                print("-------------\nYou now gain $" + str(streakinc) +  " more money per question streak!")
                streak = 0
                
              elif pointTotal < 20:   
                os.system('cls')              
                print("-------------\nYou do not have enough money!")
                              
              else:
                os.system('cls')
                print("-------------\nYou have already purchased this!")
              continue

            elif upgrade == "2" :
              if pointTotal >= 200 and streakinc < 10:
                streakinc = 10
                pointTotal = pointTotal - 200
                os.system('cls')
                print("-------------\nYou now gain $" + str(streakinc) +  " more money per question streak!")
                streak = 0
                
              elif pointTotal < 200:   
                os.system('cls')              
                print("-------------\nYou do not have enough money!")
                              
              else:
                os.system('cls')
                print("-------------\nYou have already purchased this!")
              continue

            elif upgrade == "3" :
              if pointTotal >= 2000 and streakinc < 50:
                streakinc = 50
                pointTotal = pointTotal - 2000
                os.system('cls')
                print("-------------\nYou now gain $" + str(streakinc) +  " more money per question streak!")
                streak = 0
                
              elif pointTotal < 2000:   
                os.system('cls')              
                print("-------------\nYou do not have enough money!")
                              
              else:
                os.system('cls')
                print("-------------\nYou have already purchased this!")
              continue

            elif upgrade == "4" :
              if pointTotal >= 20000 and streakinc < 250:
                streakinc = 250
                pointTotal = pointTotal - 20000
                os.system('cls')
                print("-------------\nYou now gain $" + str(streakinc) +  " more money per question streak!")
                streak = 0
                
              elif pointTotal < 20000:   
                os.system('cls')              
                print("-------------\nYou do not have enough money!")
                              
              else:
                os.system('cls')
                print("-------------\nYou have already purchased this!")
              continue

            elif upgrade == "5" :
              if pointTotal >= 200000 and streakinc < 1200:
                streakinc = 1200
                pointTotal = pointTotal - 200000
                os.system('cls')
                print("-------------\nYou now gain $" + str(streakinc) +  " more money per question streak!")
                streak = 0
                
              elif pointTotal < 200000:   
                os.system('cls')              
                print("-------------\nYou do not have enough money!")
                              
              else:
                os.system('cls')
                print("-------------\nYou have already purchased this!")
              continue

            elif upgrade == "6" :
              if pointTotal >= 2000000 and streakinc < 6500:
                streakinc = 6500
                pointTotal = pointTotal - 2000000
                os.system('cls')
                print("-------------\nYou now gain $" + str(streakinc) +  " more money per question streak!")
                streak = 0
                
              elif pointTotal < 2000000:   
                os.system('cls')              
                print("-------------\nYou do not have enough money!")
                              
              else:
                os.system('cls')
                print("-------------\nYou have already purchased this!")
              continue

            elif upgrade == "7" :
              if pointTotal >= 20000000 and streakinc < 35000:
                streakinc = 35000
                pointTotal = pointTotal - 20000000
                os.system('cls')
                print("-------------\nYou now gain $" + str(streakinc) +  " more money per question streak!")
                streak = 0
                
              elif pointTotal < 20000000:   
                os.system('cls')              
                print("-------------\nYou do not have enough money!")
                              
              else:
                os.system('cls')
                print("-------------\nYou have already purchased this!")
              continue

            elif upgrade == "8" :
              if pointTotal >= 200000000 and streakinc < 175000:
                streakinc = 175000
                pointTotal = pointTotal - 200000000
                os.system('cls')
                print("-------------\nYou now gain $" + str(streakinc) +  " more money per question streak!")
                streak = 0
                
              elif pointTotal < 200000000:   
                os.system('cls')              
                print("-------------\nYou do not have enough money!")
                              
              else:
                os.system('cls')
                print("-------------\nYou have already purchased this!")
              continue

            else:
              os.system('cls')
              continue
              
          if shopAns == "C" or shopAns == "c":
            os.system('cls')
            upgrade = input("-------------\nMoney Multiplier\n-------------\n Current money: $" + str(pointTotal) + "\n\n 1. 1.5x multiplier (Price: $50) \n 2. 2x multiplier (Price: $300) \n 3. 3x multiplier (Price: $2,000) \n 4. 5x multiplier (Price: $12,000) \n 5. 8x multiplier (Price: $85,000) \n 6. 12x multiplier (Price: $700,000) \n 7. 18x multiplier (Price: $6,500,000) \n 8. 30x multiplier (Price: $65,000,000) \n\n 9. Exit \n-------------\n You say: ")

            while upgrade != "1" and upgrade != "2" and upgrade != "3" and upgrade != "4" and upgrade != "5" and upgrade != "6" and upgrade != "7" and upgrade != "8" and upgrade != "9":
              os.system('cls')
              print("-------------\nInvalid")
              
              upgrade = input("-------------\nStreak Bonus\n-------------\n Current money: $" + str(pointTotal) + "\n\n 1. $3 streak bonus (Price: $20) \n 2. $10 streak bonus (Price: $200) \n 3. $50 streak bonus (Price: $2,000) \n 4. $250 streak bonus (Price: $20,000) \n 5. $1,200 streak bonus (Price: $200,000) \n 6. $6,500 streak bonus (Price: $2,000,000) \n 7. $35,000 streak bonus (Price: $20,000,000) \n 8. $175,000 streak bonus (Price: $200,000,000) \n\n 9. Exit \n-------------\n You say: ")
            
            if upgrade == "1" :
              if pointTotal >= 50 and pointX < 1.5:
                pointX = 1.5
                pointTotal = pointTotal - 50
                os.system('cls')
                print("-------------\nYour points gained is now multiplied by " + str(pointX) + "x!")
                streak = 0
                
              elif pointTotal < 50:   
                os.system('cls')              
                print("-------------\nYou do not have enough money!")
                              
              else:
                os.system('cls')
                print("-------------\nYou have already purchased this!")
              continue

            if upgrade == "2" :
              if pointTotal >= 300 and pointX < 2:
                pointX = 2
                pointTotal = pointTotal - 300
                os.system('cls')
                print("-------------\nYour points gained is now multiplied by " + str(pointX) + "x!")
                streak = 0
                
              elif pointTotal < 300:   
                os.system('cls')              
                print("-------------\nYou do not have enough money!")
                              
              else:
                os.system('cls')
                print("-------------\nYou have already purchased this!")
              continue

            if upgrade == "3" :
              if pointTotal >= 2000 and pointX < 3:
                pointX = 3
                pointTotal = pointTotal - 2000
                os.system('cls')
                print("-------------\nYour points gained is now multiplied by " + str(pointX) + "x!")
                streak = 0
                
              elif pointTotal < 2000:   
                os.system('cls')              
                print("-------------\nYou do not have enough money!")
                              
              else:
                os.system('cls')
                print("-------------\nYou have already purchased this!")
              continue

            if upgrade == "4" :
              if pointTotal >= 12000 and pointX < 5:
                pointX = 5
                pointTotal = pointTotal - 12000
                os.system('cls')
                print("-------------\nYour points gained is now multiplied by " + str(pointX) + "x!")
                streak = 0
                
              elif pointTotal < 12000:   
                os.system('cls')              
                print("-------------\nYou do not have enough money!")
                              
              else:
                os.system('cls')
                print("-------------\nYou have already purchased this!")
              continue

            if upgrade == "5" :
              if pointTotal >= 85000 and pointX < 8:
                pointX = 8
                pointTotal = pointTotal - 85000
                os.system('cls')
                print("-------------\nYour points gained is now multiplied by " + str(pointX) + "x!")
                streak = 0
                
              elif pointTotal < 85000:   
                os.system('cls')              
                print("-------------\nYou do not have enough money!")
                              
              else:
                os.system('cls')
                print("-------------\nYou have already purchased this!")
              continue

            if upgrade == "6" :
              if pointTotal >= 700000 and pointX < 12:
                pointX = 12
                pointTotal = pointTotal - 700000
                os.system('cls')
                print("-------------\nYour points gained is now multiplied by " + str(pointX) + "x!")
                streak = 0
                
              elif pointTotal < 700000:   
                os.system('cls')              
                print("-------------\nYou do not have enough money!")
                              
              else:
                os.system('cls')
                print("-------------\nYou have already purchased this!")
              continue

            if upgrade == "7" :
              if pointTotal >= 6500000 and pointX < 18:
                pointX = 18
                pointTotal = pointTotal - 6500000
                os.system('cls')
                print("-------------\nYour points gained is now multiplied by " + str(pointX) + "x!")
                streak = 0
                
              elif pointTotal < 6500000:   
                os.system('cls')              
                print("-------------\nYou do not have enough money!")
                              
              else:
                os.system('cls')
                print("-------------\nYou have already purchased this!")
              continue

            if upgrade == "8" :
              if pointTotal >= 65000000 and pointX < 30:
                pointX = 30
                pointTotal = pointTotal - 65000000
                os.system('cls')
                print("-------------\nYour points gained is now multiplied by " + str(pointX) + "x!")
                streak = 0
                
              elif pointTotal < 65000000:   
                os.system('cls')              
                print("-------------\nYou do not have enough money!")
                              
              else:
                os.system('cls')
                print("-------------\nYou have already purchased this!")
              continue

            else:
              os.system('cls')
              continue

          if shopAns == "D" or shopAns == "d":
            os.system('cls')
            continue

          else:
            os.system('cls')
            print("-------------\nInvalid")
            continue
              
              
################################################################
              
          
        else:
          inputAns = 3  


      

      #We know that order[0] is always the answer, so if the users input is equal to that, than the answer is correct.
        if order[0] == inputAns:
                    
          
          #Point X is a multiplier which affects the point gain combined with the streak bonus.          
          pointTotal = pointTotal + (pointGain + streak) * pointX
          
          
          
         #Users gains 1 life for every 10 questions correct IN A ROW. Buying from the shop DOES NOT reset this counter.
          if combo % 10 == 0 and combo != 0:
                       
            lives = lives + 1
            print("-------------\nYour lives have been increased by 1!\n-------------")
            #Streak is increased by the previous streak points plus the current increment (standard streakinc is 1)
          print("CORRECT!" + "(+$" + str((pointGain + streak) * pointX) + ") \n lives left: " + str(lives))
          combo = combo + 1
          streak = streak + streakinc
          
          
          

          
        else:
# If question incorrect, you lose the same amount of points, your lives, and the streak + combo reset to 0.
          pointTotal = pointTotal - (pointGain + streak) * pointX
          
          lives = lives - 1
          print("INCORRECT!" + "(-$" + str((pointGain + streak) * pointX) + ") \n lives left: " + str(lives))
          streak = 0
          combo = 0
          #Increment is increased, to go to the next question. Your current points/money is shown
        increment = increment + 1
        print("Current Money: $" + str(pointTotal))

        
        
      #This statement makes the ranindex list reset when the end of the list is reached. This allows each term to have been asked once.
        if increment == listTotal:
      
          ranindex = random.sample(range(listTotal), listTotal)
          increment = 0
          
        if lives <= 0:
          
#Shows points made and ends game when all lives are lost.
          os.system('cls')
          print("-----------------------\nGAME OVER\n-----------------------\nYou made: $" + str(pointTotal) )
          break
  
      
          

##########Main Code####################################

print("Welcome to the Study game!\n-----------")
#A different form of end statement, made a variable that when it equals 1, it stops asking for input.
while End == 0:
    Trans = input(
        "What language do you want to translate to?:\n A. English --> Spanish\n B. Spanish --> English\n-------------\nYou say: "

    )
    os.system('cls')
    if Trans == "A" or Trans == "a":

       scramble(ENGpool, SPpool, "Spanish") 
       End = 1

    elif Trans == "B" or Trans == "b":

        scramble(SPpool, ENGpool, "English")
        End = 1
    else:
        print("-----------\nYour answer is invalid, try again.\n-----------")







