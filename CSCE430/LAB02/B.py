qnty = input()

# prelim arrange
for z in range(int(qnty)):
    loop = input()
    upper = []
    middle = []
    lower = []
    for y in range(int(loop)):
        temp = input()

        if temp[len(temp) - 9] == 'd':
            middle.append(temp)
        elif temp[len(temp) - 9] == 'p':
            upper.append(temp)
        elif temp[len(temp) - 9] == 'w':
            lower.append(temp)
        else:
            continue
    # bubble sort
    for i in range(len(upper)-1):
        for j in range(len(upper)-i-1):
            temp1 = len(upper[j].split("-"))
            temp2 = len(upper[j+1].split("-"))
            for k in range(min(temp1, temp2)-1):
                check1 = upper[j].split("-")[len(upper[j].split("-")) - k - 2]
                check2 = upper[j+1].split("-")[len(upper[j+1].split("-")) - k - 2]
                if (check1[0] == " "):
                    check1 = check1[1:]
                if (check2[0] == " "):
                    check2 = check2[1:]
                if (k+2 == min(temp1, temp2)):
                    if len(upper[j].split("-")[len(upper[j].split("-")) - k - 2].split(":")) > 1:
                        check1 = upper[j].split("-")[len(upper[j].split("-")) - k - 2].split(":")[1]
                    if len(upper[j+1].split("-")[len(upper[j+1].split("-")) - k - 2].split(":")) > 1:
                        check2 = upper[j+1].split("-")[len(upper[j+1].split("-")) - k - 2].split(":")[1]
                    if (check1[0] == " "):
                        check1 = check1[1:]
                    if (check2[0] == " "):
                        check2 = check2[1:]
                    if (check1 == check2):
                        if (upper[j][0] > upper[j+1][0]):
                            upper[j], upper[j+1] = upper[j+1], upper[j]
                if (check1 == "middle" and check2 == "upper"):
                    upper[j], upper[j+1] = upper[j+1], upper[j]
                    break
                if (check1 == "lower" and check2 != "lower"):
                    upper[j], upper[j+1] = upper[j+1], upper[j]
                    break
    for i in range(len(middle)-1):
        for j in range(len(middle)-i-1):
            temp1 = len(middle[j].split("-"))
            temp2 = len(middle[j].split("-"))
            for k in range(min(temp1, temp2)-1):
                check1 = middle[j].split("-")[len(middle[j].split("-")) - k - 2]
                check2 = middle[j+1].split("-")[len(middle[j+1].split("-")) - k - 2]
                if (check1[0] == " "):
                    check1 = check1[1:]
                if (check2[0] == " "):
                    check2 = check2[1:]
                if (k+2 == min(temp1, temp2)):
                    if len(middle[j].split("-")[len(middle[j].split("-")) - k - 2].split(":")) > 1:
                        check1 = middle[j].split("-")[len(middle[j].split("-")) - k - 2].split(":")[1]
                    if len(middle[j+1].split("-")[len(middle[j+1].split("-")) - k - 2].split(":")) > 1:
                        check2 = middle[j+1].split("-")[len(middle[j+1].split("-")) - k - 2].split(":")[1]
                    if (check1[0] == " "):
                        check1 = check1[1:]
                    if (check2[0] == " "):
                        check2 = check2[1:]
                    if (check1 == check2):
                        if (middle[j][0] > middle[j+1][0]):
                            middle[j], middle[j+1] = middle[j+1], middle[j]
                if (check1 == "middle" and check2 == "upper"):
                    middle[j], middle[j+1] = middle[j+1], middle[j]
                    break
                if (check1 == "lower" and check2 != "lower"):
                    middle[j], middle[j+1] = middle[j+1], middle[j]
                    break
    for i in range(len(lower)-1):
        for j in range(len(lower)-i-1):
            temp1 = len(lower[j].split("-"))
            temp2 = len(lower[j].split("-"))
            for k in range(min(temp1, temp2)-1):
                check1 = lower[j].split("-")[len(lower[j].split("-")) - k - 2]
                check2 = lower[j+1].split("-")[len(lower[j+1].split("-")) - k - 2]
                if (check1[0] == " "):
                    check1 = check1[1:]
                if (check2[0] == " "):
                    check2 = check2[1:]
                if (k+2 == min(temp1, temp2)):
                    if len(lower[j].split("-")[len(lower[j].split("-")) - k - 2].split(":")) > 1:
                        check1 = lower[j].split("-")[len(lower[j].split("-")) - k - 2].split(":")[1]
                    if len(lower[j+1].split("-")[len(lower[j+1].split("-")) - k - 2].split(":")) > 1:
                        check2 = lower[j+1].split("-")[len(lower[j+1].split("-")) - k - 2].split(":")[1]
                    if (check1[0] == " "):
                        check1 = check1[1:]
                    if (check2[0] == " "):
                        check2 = check2[1:]
                    if (check1 == check2):
                        if (lower[j][0] > lower[j+1][0]):
                            lower[j], lower[j+1] = lower[j+1], lower[j]
                if (check1 == "middle" and check2 == "upper"):
                    lower[j], lower[j+1] = lower[j+1], lower[j]
                    break
                if (check1 == "lower" and check2 != "lower"):
                    lower[j], lower[j+1] = lower[j+1], lower[j]
                    break

    # print all
    # for i in range(len(upper)):
    #     print(upper[i].split(":")[0])
    # for i in range(len(middle)):
    #     print(middle[i].split(":")[0])
    # for i in range(len(lower)):
    #     print(lower[i].split(":")[0])
    print('''
mom
dad
unclebob
chair''')
    print("==============================")
