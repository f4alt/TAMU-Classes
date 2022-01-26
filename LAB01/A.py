in_str = raw_input()
response_str = ""

i=0
while i < len(in_str):
    if i+1 < len(in_str) and in_str[i+1] != in_str[i]:
        if i+2 < len(in_str) and in_str[i+2] != in_str[i] and in_str[i+1] != in_str[i+2]:
            response_str += 'C'
            i += 3
            # print("I:", i)
        else:
            i += 1
    #         print("inc1:", i)
    # else:
    #     i+=1
    # if i == len(in_str):
    #     break
    else:
        # i += 1
        if in_str[i] == 'R':
            response_str += 'S'
        elif in_str[i] == 'B':
            response_str += 'K'
        elif in_str[i] == 'L':
            response_str += 'H'
        i += 1
    # print("inc2:", i)

print(response_str)
