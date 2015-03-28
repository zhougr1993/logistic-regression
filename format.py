import sys
def initial_size(x):
    x = float(x)
    return float(x/100)
def formart(feature):
    out = []
    i = 1
    for x in feature:
        out.append(str(i)+':'+str(x))
        i+=1
    return out
if __name__ == "__main__":
    if len(sys.argv)<2:
        print sys.argv[0],'output file'
        exit()
    with open(sys.argv[1],'w') as out_f:
        for line in sys.stdin:
            line = line.strip()
            line = line.split(',')
            lable = str(line[4])
            if lable == 'Iris-setosa':
            #line = map(initial_size,line)
                line.remove(lable)
                lable = '0'
                line = formart(line)
                out_f.write(lable+' ' + ' '.join(line)+'\n')
            else:
                line.remove(lable)
                lable = '1'
                line = formart(line)
                out_f.write(lable+ ' ' +' '.join(line)+'\n')
    out_f.close()
