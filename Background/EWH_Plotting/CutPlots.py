
def EnergyCuts():

    import matplotlib.pyplot as plt

    plt.rc('axes', linewidth = 2)

    font = {'family' : 'arial', 'weight' : 'bold'}
    plt.rc('font', **font)
    plt.rc('xtick.minor', size = 5, width = 1)
    plt.rc('ytick.minor', size = 5, width = 1)
    plt.rc('xtick.major', width = 1.5)
    plt.rc('ytick.major', width = 1.5)

    plt.rc('xtick.minor', size = 5)
    plt.rc('ytick.minor', size = 5)
    plt.rc('mathtext', default = 'regular')

    Energy_ = [5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 75, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 2000, 5000]
    #SurvivedE_ = [114, 113, 112, 110, 108, 102, 100, 93, 85, 77, 54, 32, 2];
    SurvivedE_ = [291, 291, 291, 291, 291, 291, 291, 289, 287, 284, 275, 248, 135, 94, 71, 56, 45, 37, 32, 27, 24, 6, 2]
    SurvivedE_TwoPi0 = [291, 290, 289, 287, 285, 282, 272, 262, 247, 232, 175, 120, 56, 39, 30, 21, 20, 15, 14, 11, 10, 3, 0]
    #plt.plot(Energy_, [i*17.9 for i in SurvivedE_],'-o')

    a, = plt.plot(Energy_, [i*17.9 for i in SurvivedE_TwoPi0],marker='o')

    plt.hold(True)

    leg = plt.legend([a], [' $\pi^0$ Events with Three Photons \n Surviving Cut, Including Two \n from $\pi^0$ Surviving Cut'], loc = 0, frameon = False, labelspacing = .4, handlelength = 2, handletextpad = .5, borderaxespad = 2)

    plt.title('$\pi^0$ Events with Three Photons Above Energy Cut', fontsize = '18')
    plt.xlabel('Energy Cut (MeV)', fontsize = '18')
    plt.ylabel('Number of Events', fontsize = '18')
    plt.xlim(0,1000)
    plt.ylim(0,5500)

    for l in plt.gca().get_xticklines() + plt.gca().get_yticklines():
        l.set_markersize(12)

    for t in leg.get_texts():
        t.set_fontsize('18')
        
    plotname = 'EnergyCutsMCC5_Final.jpg'

    plt.savefig(plotname)
    plt.hold(False)
    plt.show()

def DistanceCuts():

    import matplotlib.pyplot as plt

    plt.rc('axes', linewidth = 2)

    font = {'family' : 'arial', 'weight' : 'bold'}
    plt.rc('font', **font)
    plt.rc('xtick.minor', size = 5, width = 1)
    plt.rc('ytick.minor', size = 5, width = 1)
    plt.rc('xtick.major', width = 1.5)
    plt.rc('ytick.major', width = 1.5)

    plt.rc('xtick.minor', size = 5)
    plt.rc('ytick.minor', size = 5)
    plt.rc('mathtext', default = 'regular')

    Distance_ = [0.1, 0.2, 0.3, 0.5, 1, 2, 5, 10]
    #SurvivedE_ = [114, 113, 112, 110, 108, 102, 100, 93, 85, 77, 54, 32, 2];
    SurvivedD_ = [182,206,221,233,248,261,270,271]
    a, = plt.plot(Distance_, [i*17.9 for i in SurvivedD_],'-o')

    plt.hold(True)

    plt.title('$\pi^0$ Events With Photon Groups Within Distance Cut', fontsize = '18')
    plt.xlabel('Distance Cut (cm)', fontsize = '18')
    plt.ylabel('Number of Events', fontsize = '18')
    plt.xlim(0,10)
    plt.ylim(0,5500)

    leg = plt.legend([a], [' $\pi^0$ Events with Three Grouped Photons \n Surviving Cut, Including Two \n from $\pi^0$ in Group Surviving Cut'], loc = 0, frameon = False, labelspacing = .4, handlelength = 2, handletextpad = .5, borderaxespad = 2)

    for l in plt.gca().get_xticklines() + plt.gca().get_yticklines():
        l.set_markersize(12)
        
    for t in leg.get_texts():
        t.set_fontsize('18')

    plotname = 'DistanceCutsMCC5_Final.jpg'

    plt.savefig(plotname)
    plt.hold(False)
    plt.show()

#def DistCuts():
