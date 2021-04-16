
f_init = open("../run_init/out.data","r")
f_conv = open("../run_init/out.convert","w")


for l_init in f_init:
    w_init = l_init[:-1].split(" ")
    e_init = int( w_init[0] )
    ss = ""
    for i in range( len(w_init)-1 ):
        ss += w_init[i] + " "
    f_conv.write( ss + " -" + w_init[-1] + "\n" )

f_init.close()
f_conv.close()



f_scat = open("../run_scat/out.data","r")
f_init = open("../run_init/out.convert","r")
f_merg = open("merged.data","w")


e_init = 0
e_scat = 0
EVENT  = 0
not_first  = False
for l_init in f_init:
    w_init = l_init[:-1].split(" ")
    e_init = int( w_init[0] )
    if e_init > EVENT:
        if not_first:
            f_merg.write( l_scat ) # write prev line
        not_first = True
        while e_scat < e_init:
            l_scat = f_scat.readline()
            if len(l_scat)<1:
                break
            e_scat = int( l_scat[:-1].split(" ")[0] )
            f_merg.write( l_scat ) # write 
        EVENT += 1
    f_merg.write( l_init )


if e_init > EVENT:
    f_merg.write( l_scat ) # write prev line
    while e_scat < e_init:
        l_scat = f_scat.readline()
        e_scat = l_scat[:-1].split(" ")[0]
        f_merg.write( l_scat ) # write 


f_init.close()
f_merg.close()
f_scat.close()

