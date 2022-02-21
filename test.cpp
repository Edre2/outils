#include "outils.h"
// #include "outils_big_int.h"
#include <iomanip> // for std::setprecision()
#include <fstream>
using namespace std;

int main()
{

    ////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////
    //////////////////// PARTIE SUR LES TEXTES /////////////////////
    ////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////

    // textes :
        // string texte = "To be, or not to be, that is the question—Whether 'tis Nobler in the mind to suffer The Slings and Arrows of outrageous Fortune,Or to take Arms against a Sea of troubles,And by opposing end them?William Shakespeare - Hamlet";

        // string texte = "Rages de Césars\n Arthur Rimbaud\n \n L’homme pâle, le long des pelouses fleuries,\n Chemine, en habit noir, et le cigare aux dents :\n L’Homme pâle repense aux fleurs des Tuileries\n – Et parfois son oeil terne a des regards ardents…\n \n Car l’Empereur est soûl de ses vingt ans d’orgie !\n Il s’était dit :  » Je vais souffler la liberté\n Bien délicatement, ainsi qu’une bougie ! « \n La liberté revit ! Il se sent éreinté !\n \n Il est pris. – Oh ! quel nom sur ses lèvres muettes\n Tressaille ? Quel regret implacable le mord ?\n On ne le saura pas. L’Empereur a l’oeil mort.\n \n Il repense peut-être au Compère en lunettes…\n – Et regarde filer de son cigare en feu,\n Comme aux soirs de Saint-Cloud, un fin nuage bleu.\n \n Arthur Rimbaud, Poésies";

        // codé avec vigenère et les mots :

        // PEDAGOGIE
        // string texte = "GEJEY RK KIHEUS\n GFZPYG VLMHOAL\n \n P’WSPMK DGTI, AI OOTU JMW EIOOAGKA JAIXROSY, \n KLTQLNK, ST PEQMW NUWX, MX AI FIMOXM EJB GETHY : \n T’LDQPE VORM VTTHNYS GCB UPHUXG JMW IYLLKFOMW\n – TX SAXTUQW HSQ OKWR BIGRH A JSY ZIVEUDY OXLICXV… \n \n CGF R’MQEIUEAF KAX HSXL JS YMW KMQGZ OTA H’DVJIK !\n WR A’IIELT JWZ :  » RI KELS YCANJAIU LG ZOJIGXH\n BOST LIAMFAZSSMRI, ELNYW WC’YCI EOAUOM ! «\n PP PLBKFZM VTZLT ! OZ YM WTRW EXSOVXT !\n \n MO EYH VZMH. – SK ! QASR VSB WXR YSY TIKVHS SIKBXTW\n WRKGYIMAPH ? QASR ZIVVHT OAVTEREELK ZK USGH ?\n RN TS RM WPYUA VOY. T’IBTHRKIX I P’DILL SCXB.\n \n MA VHPKBYM TTYW-EZFK IY RSPPKFK MR AYQEZHKA…\n – II VHGGFJM JXPHR JS YWR RMJAXS KV JTY,\n FOSAK IYM WRIXG JM WPMQT-IZUCH, JR IIT BAIKT FOEA.\n \n OXBLJV UISPGCH, ESHSOSY";

        // BONJOUR
        // string texte = "SOTNG XV DSFJFM\n RSHUDF LZNPNDR\n \n F’YPAZN DUCF, ZR UCHX ESF YSFFVGRB TFVVFVNG,\n WYFAVWS, YE IOORH HFJF, RC ZY TJUNAS ULY RRWHM :\n C’ICZVS JRMS ENDYETS NDL ZCFIEB RYJ UIVUSLZFG\n – RC DUIGCVB GIE PSVU HYIOS N MSM IFUNARM RSRRWHM…\n TBF Y’NAJVSSHA SMK TCHU RY JFG IRBAK BBF M’CLXJS !\n VU G’YKBWG MWN :  » AF JNRG MFVTSUSL CB ZVKSLKF\n PVNB XVMWPJHYDFBG, JWHJJ EH’DBY SPITRS ! «\n FR MWONFNV SSIRH ! CC TS FNBN VSSVWHY !\n \n ZM SFC DLZT. – CU ! ZIYC OCZ BIL JFG YNJLVT AHNHNVT\n HENGMRJZYN ? EOVM FRPFYK JACUOWRCZR US GFSR ?\n BW BY CF GNDFU GBG. Y’NAJVSSHA O F’FFWY VCLK.\n \n JZ ENDYETS CNIN-VUFR JI WFNDRAS YE MIANHNVT…\n – SG ASARSRR OWFVS RR BCH TJUNAS YE GSH,\n LCGDF OHG GIZSG QN GUZOH-PUCOU, VB SRB HLBUR KZYL.\n \n BFGQIL IJAOJIX, GPSFRSM";

        // Un autre texte
        // string texte = "Sensation\n\nPar les soirs bleus d’été, j’irai dans les sentiers,\n Picoté par les blés, fouler l’herbe menue :\n Rêveur, j’en sentirai la fraîcheur à mes pieds.\n Je laisserai le vent baigner ma tête nue.\n \n Je ne parlerai pas, je ne penserai rien :\n Mais l’amour infini me montera dans l’âme,\n Et j’irai loin, bien loin, comme un bohémien,\n Par la Nature, – heureux comme avec une femme.";

        // codé avec vigenère et les mots :

        // SALUT
        // string texte = "KEYMTLIZH  ISR WYL KOTLL TLPOL V’EEY, C’ARLC WSND FXK SPHMAECM, IACZNX HAC FXK BWYL, XOFFXJ L’SYKTE XYGME : CYOWUC, D’XF SPHMARLC ES FCUBUHPOK S MPM IAEOM. CW LLCLKECUB DE GYGL BLCZFEC GT LEEY GME.  UY GW PLLEWRLC ISS, UY GW PPHLWRLC KAEY : GTAS W’UFGUC CGXIYC FW MZHMWRL XTFS W’UFW, EE D’BJAT FHAN, MCXF LZCG, UOXGX MN MIAWMTYG, HAC FT FAEOKW, – HPOKWUI WHEMP UOWC FHX XEXGX.";

        // TEST
        // string texte = "LIFLTXAHG\n \n TSK EIK LHMJL UPWNL H’WMX, N’AKTM VTGW DXL WWGMMWKL,\n TAVHXW ITV DXL FDXL, JGNEIJ E’AIJUX QWGNI :\n JXOIMK, C’IF LXRLBKEA ET JJTBGZXNV S FXW HBXHK.\n CX PSBLWWKTM DX OIFM UEAZGIJ FT XWMX RMX.\n \n CI FX IEJEXVSB IEK, CX RW IXRKXKEA KBIF :\n FTMK E’TQGNK MFYBRA FX QGGMIJT WEFL E’EEX,\n XX B’BKEA EHMF, UBIF EHMF, VHQEX NR THAIEBXR,\n HTK PS GTXMKX, – LWNKIMQ VSEFX ENXV YFX YIEFX.";

    // Test des fonctions de formattage du texte :
    // cout << supprimerAccents(texte) << "\n";
    // cout << jolitexte(texte) << "\n";
    // cout << metttreMaj(texte) << "\n";

     // cout << indexFromString(texte, 'b');

     // cout << index_of_coincidence(texte) << endl ;

     // vector<int> distance;
     // kasiski_test(texte, distance, 3);
     //     for(int i =0; i < int(distance.size()); i++)
     // cout << distance[i] << endl;

    // cout << get_key_length(texte) << endl;
    // cout << get_key(texte) << endl;

    // Test du codage vigenère :
    // string mot = "abcd";
    // cin >> mot;
    // cout << codagev(texte, mot) << "\n";
    // cout << jolitexte(decodagev(texte, mot)) << "\n" ;

    // test du décodage automatique avec vigenère
    // cout << decodage_automatique_v(texte) << "\n";
    // cout << jolitexte(decodagev(texte, decodage_automatique_v(texte))) << "\n";

    // test de l'analyse de texte :
    // cout << analyse(texte) << "\n";
    // vector<int> alphabet;
    // analyse(texte, alphabet);
    // for(int i = 0; i < 26; i++)
    //     cout << char(i + 65) << " : " << alphabet[i] << "\n";

    // string substitution = "abcdefghijklmnopqrstuvwxyz";
    // cout << codages(texte, substitution) << endl;  
    // cout << decodages(texte, substitution) << endl;  

    ////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////
    //////////////////// PARTIE SUR LES NOMBRES ////////////////////
    ////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////

     // std::cout << std::setprecision(2); // show 16 digits of precision


    // test de la conversion vers d'autre bases :
    // string nb = "";
    // int base = 0, base2 = 0;
    // cin >> nb >> base >> base2;
    // cout << convertBase(nb, base, base2);

    // long long int nb = 0;
    // cin >> nb;

    // test des facteurs premiers :
    // vector<int> factpremsn;
    // factprems(nb, factpremsn);
    // for(int i = 0; i < int(factpremsn.size()); i++)
    //     cout << factpremsn[i] << "\n";

    // test des nombres premiers :
    // vector<int> nbsprems;
    // NbsPremsjusquaN(nb, nbsprems);
    // for(int i = 0; i < int(nbsprems.size()); i++)
    //     cout << nbsprems[i] << "\n";


    // test de la suite de fibonnacci
    // for(int i=0; i < 47; i++)
    //     cout << fibo(i) << endl;

    // test de l'approximation de farey
    // float nb1 = 0.67485475;
    // cin >> nb1;
    // cout << farey_approximation(nb1, 10000000) << "\n\n\n";
 
    // test de l'approximatin de la racine carré
    // int nb = 0;
    // cin >> nb;
    // cout << approximation_racinecarre(nb, 100) << endl;
    // cout << pow(nb, 1.0/2) << endl;

    // test de l'approximatin de la racine cubique
    // int nb = 0;
    // cin >> nb;
    // cout << approximation_racinecubique(nb, 100) << endl;
    // cout << pow(nb, 1.0/2) << endl;

    // Grangs nombres (include outils_big_int.h en haut)
    // boost::multiprecision::cpp_int a = 838947915628470415334561123513;
    // boost::multiprecision::cpp_int a = 500912466059711711;
    // if(estprems_big(a))
    //     cout << "yes";
    // else
    //     cout << "no";

    // cout << eval("1+1") << endl;
    // cout << op(3,1, '/') << "\n";
    // cout << calculer_notation_polonaise_inversee("1.9 2 + 2.5 * 1.2 ^") << endl;
    //cout << calculer_notation_polonaise_inversee("1 3 5 2 + * +") << endl;
    
    // cout << calculer("32*(48+2)-23^2") << endl;

    return EXIT_SUCCESS;
}
