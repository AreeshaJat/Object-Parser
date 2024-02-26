def readppm(ppmFileName):
    content = []
    with open(ppmFileName) as f:
        lines = f.readlines()
        if lines[0][0] == 'P':
            if lines[0][1] == '6':
                content = read_p6_ppm(ppmFileName)
            else:
                for line in lines:
                    if line[0] != '#':
                        for t in line.split():
                            content.append(t)
        else:
            return -1

    return content

def read_p6_ppm(ppmFileName):
    components = []

    f = open(ppmFileName, "rb")
    all = f.read()

    info = all.split('\n', 4) # for CRFL
    for i in info[:4]:
        if i[0] == '#':
            continue
        if len(i.split()) > 1:
            size = i.split()
            components.append(str(size[0]))
            components.append(str(size[1]))
            continue
        components.append(str(i))

    a = list(info[4])
    for i in a:
        val = int(i.encode('hex'),  16)
        if val == 10:
            if prev_val != 13:
                components.append(str(val))
        else:
            components.append(str(val))
        prev_val = val

    return components
