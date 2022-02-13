#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>
#include "outils.cpp"
#include <iomanip> // for std::setprecision()
#include <string>
#include <vector>
#include <fstream>
using namespace std;

int main()
{

    // boost::multiprecision::cpp_int a = 838947915628470415334561123513;
    // boost::multiprecision::cpp_int a = 500912466059711711;
    // if(estprems_big(a))
    //     cout << "yes";
    // else
    // cout << "no";
    // std::cout << std::setprecision(2); // show 16 digits of precision

   // string text = "Sensation\te laisserai le vent baigner ma tête nue.\n \n Je ne parlerai pas, je ne penserai rien :\n Mais l’amour infini me montera dans l’âme,\n Et j’irai loin, bien loin, comme un bohémien,\n Par la Nature, – heureux comme avec une femme.";

   // string text = "Le livre, cet « assemblage d’un assez grand nombre de feuilles portant des signes destinés à être lus » (Le Nouveau Petit Robert) n’a pas toujours eu la forme tenue pour classique en Occident — celle du codex, apparue au début de l’ère chrétienne : volume constitué de cahiers et pourvu d’une couverture permettant de le tenir fermé. Il a pu se présenter en d’autres temps et lieux sous la forme de tablettes d’argile, de stèles de pierre, de rouleaux de papyrus, de tablettes enduites de cire, de feuilles de végétaux, d’étoffes, etc. Sans oublier que de nos jours il peut aussi se résumer à un enregistrement numérique lisible sur écran.  L’histoire de cet objet nous en dit beaucoup sur sa conception, son influence et sur les usages qui ont pu en être faits. La forme codex, qui a caractérisé le livre manuscrit de la fin de l’Antiquité et du Moyen Âge, puis le volume imprimé de la « galaxie Gutenberg » (Marshall McLuhan) — lequel a inauguré les Temps modernes et nous imprègne encore —, marque incontestablement un apogée du développement de l’écrit. Un apogée où chaque avancée civilisationnelle trouve sa traduction voire son origine dans un ou plusieurs livres.  Un apogée où les grands artisans et artistes du livre, auteurs, enlumineurs, copistes, relieurs, parcheminiers, mais aussi plus tard écrivains, imprimeurs, éditeurs, graveurs, créateurs de caractères ou de décors, illustrateurs, papetiers, inventeurs, semblent avoir tous été animés par l’idée d’une cause utile voire noble à illustrer, celle de la diffusion la plus large, parfois même de la propagande.  Consciemment ou non, ces « gens du livre » ont successivement travaillé au service de l’Université et de ses doctrines, de l’Humanisme, de la Réforme puis de la Contre-Réforme, de la Monarchie absolue et de son classicisme, des Lumières, de la Révolution, du Progrès scientifique, économique ou social, de la Diversité culturelle ou de la Pensée unique, etc.  Toutefois, même à l’époque où les historiens l’ont dit « triomphant » (fin XVIIe–début XIXe siècle) en Occident, le livre n’a jamais été placé en situation de « monopole médiatique ». Il a pris toute sa place sur fond d’analphabétisme dans un monde dominé d’abord par la communication orale, avant de connaître la concurrence de la presse, puis de voir émerger, à partir de l’extrême fin du XIXe siècle , une succession de nouveaux supports (cinéma, téléphone, radio, télévision, informatique, Internet), qui ont pu mettre en question sa position, voire ont menacé, selon certains auteurs, son existence même. Ce serait pourtant une lourde erreur que de dire le livre « condamné ». Il ne s’est jamais produit ni vendu autant de livres dans l’histoire de l’humanité qu’en ce début de XXIe siècle. Il est donc au moins prématuré de ne l’envisager que sous l’angle d’une sorte d’« archéologie des médias ».  Non seulement la « fin de l’histoire du livre » n’est pas écrite mais « la culture livresque est un enjeu énorme » pour l’humanisme contemporain (Henri-Jean Martin), et l’existence même du livre constitue l’un des gages de la liberté de l’homme moderne.";
   
    // string text = "To be, or not to be, that is the question—Whether 'tis Nobler in the mind to suffer The Slings and Arrows of outrageous Fortune,Or to take Arms against a Sea of troubles,And by opposing end them?William Shakespeare - Hamlet";

   // string text = "Rages de Césars\n Arthur Rimbaud\n \n L’homme pâle, le long des pelouses fleuries,\n Chemine, en habit noir, et le cigare aux dents :\n L’Homme pâle repense aux fleurs des Tuileries\n – Et parfois son oeil terne a des regards ardents…\n \n Car l’Empereur est soûl de ses vingt ans d’orgie !\n Il s’était dit :  » Je vais souffler la liberté\n Bien délicatement, ainsi qu’une bougie ! « \n La liberté revit ! Il se sent éreinté !\n \n Il est pris. – Oh ! quel nom sur ses lèvres muettes\n Tressaille ? Quel regret implacable le mord ?\n On ne le saura pas. L’Empereur a l’oeil mort.\n \n Il repense peut-être au Compère en lunettes…\n – Et regarde filer de son cigare en feu,\n Comme aux soirs de Saint-Cloud, un fin nuage bleu.\n \n Arthur Rimbaud, Poésies";

   // codé avec vigenère et les mots :

   // PEDAGOGIE
   // string text = "GEJEY RK KIHEUS\n GFZPYG VLMHOAL\n \n P’WSPMK DGTI, AI OOTU JMW EIOOAGKA JAIXROSY, \n KLTQLNK, ST PEQMW NUWX, MX AI FIMOXM EJB GETHY : \n T’LDQPE VORM VTTHNYS GCB UPHUXG JMW IYLLKFOMW\n – TX SAXTUQW HSQ OKWR BIGRH A JSY ZIVEUDY OXLICXV… \n \n CGF R’MQEIUEAF KAX HSXL JS YMW KMQGZ OTA H’DVJIK !\n WR A’IIELT JWZ :  » RI KELS YCANJAIU LG ZOJIGXH\n BOST LIAMFAZSSMRI, ELNYW WC’YCI EOAUOM ! «\n PP PLBKFZM VTZLT ! OZ YM WTRW EXSOVXT !\n \n MO EYH VZMH. – SK ! QASR VSB WXR YSY TIKVHS SIKBXTW\n WRKGYIMAPH ? QASR ZIVVHT OAVTEREELK ZK USGH ?\n RN TS RM WPYUA VOY. T’IBTHRKIX I P’DILL SCXB.\n \n MA VHPKBYM TTYW-EZFK IY RSPPKFK MR AYQEZHKA…\n – II VHGGFJM JXPHR JS YWR RMJAXS KV JTY,\n FOSAK IYM WRIXG JM WPMQT-IZUCH, JR IIT BAIKT FOEA.\n \n OXBLJV UISPGCH, ESHSOSY";

   // cout << index_of_coincidence(text) << endl ;

   // BONJOUR
   // string text = "SOTNG XV DSFJFM\n RSHUDF LZNPNDR\n \n F’YPAZN DUCF, ZR UCHX ESF YSFFVGRB TFVVFVNG,\n WYFAVWS, YE IOORH HFJF, RC ZY TJUNAS ULY RRWHM :\n C’ICZVS JRMS ENDYETS NDL ZCFIEB RYJ UIVUSLZFG\n – RC DUIGCVB GIE PSVU HYIOS N MSM IFUNARM RSRRWHM…\n TBF Y’NAJVSSHA SMK TCHU RY JFG IRBAK BBF M’CLXJS !\n VU G’YKBWG MWN :  » AF JNRG MFVTSUSL CB ZVKSLKF\n PVNB XVMWPJHYDFBG, JWHJJ EH’DBY SPITRS ! «\n FR MWONFNV SSIRH ! CC TS FNBN VSSVWHY !\n \n ZM SFC DLZT. – CU ! ZIYC OCZ BIL JFG YNJLVT AHNHNVT\n HENGMRJZYN ? EOVM FRPFYK JACUOWRCZR US GFSR ?\n BW BY CF GNDFU GBG. Y’NAJVSSHA O F’FFWY VCLK.\n \n JZ ENDYETS CNIN-VUFR JI WFNDRAS YE MIANHNVT…\n – SG ASARSRR OWFVS RR BCH TJUNAS YE GSH,\n LCGDF OHG GIZSG QN GUZOH-PUCOU, VB SRB HLBUR KZYL.\n \n BFGQIL IJAOJIX, GPSFRSM";

    //vector<int> distance;
    // kasiski_test(text, distance, 3);

   // for(int i =0; i < int(distance.size()); i++)
   //  cout << distance[i] << endl;

   // cout << get_key_length(text) << endl;
   // cout << get_key(text) << endl;

   // Un autre texte
   // string text = "Sensation\n\nPar les soirs bleus d’été, j’irai dans les sentiers,\n Picoté par les blés, fouler l’herbe menue :\n Rêveur, j’en sentirai la fraîcheur à mes pieds.\n Je laisserai le vent baigner ma tête nue.\n \n Je ne parlerai pas, je ne penserai rien :\n Mais l’amour infini me montera dans l’âme,\n Et j’irai loin, bien loin, comme un bohémien,\n Par la Nature, – heureux comme avec une femme.";

   // codé avec vigenère et les mots :

   // SALUT
   // string text = "KEYMTLIZH  ISR WYL KOTLL TLPOL V’EEY, C’ARLC WSND FXK SPHMAECM, IACZNX HAC FXK BWYL, XOFFXJ L’SYKTE XYGME : CYOWUC, D’XF SPHMARLC ES FCUBUHPOK S MPM IAEOM. CW LLCLKECUB DE GYGL BLCZFEC GT LEEY GME.  UY GW PLLEWRLC ISS, UY GW PPHLWRLC KAEY : GTAS W’UFGUC CGXIYC FW MZHMWRL XTFS W’UFW, EE D’BJAT FHAN, MCXF LZCG, UOXGX MN MIAWMTYG, HAC FT FAEOKW, – HPOKWUI WHEMP UOWC FHX XEXGX.";

   // TEST
   // string text = "LIFLTXAHG\n \n TSK EIK LHMJL UPWNL H’WMX, N’AKTM VTGW DXL WWGMMWKL,\n TAVHXW ITV DXL FDXL, JGNEIJ E’AIJUX QWGNI :\n JXOIMK, C’IF LXRLBKEA ET JJTBGZXNV S FXW HBXHK.\n CX PSBLWWKTM DX OIFM UEAZGIJ FT XWMX RMX.\n \n CI FX IEJEXVSB IEK, CX RW IXRKXKEA KBIF :\n FTMK E’TQGNK MFYBRA FX QGGMIJT WEFL E’EEX,\n XX B’BKEA EHMF, UBIF EHMF, VHQEX NR THAIEBXR,\n HTK PS GTXMKX, – LWNKIMQ VSEFX ENXV YFX YIEFX.";

   // Test des fonctions de formattage du text :
   // cout << supprimerAccents(text) << "\n";
   // cout << jolitexte(text) << "\n";
   // cout << metttreMaj(text) << "\n";
   
   // Test du codage vigenère :
   // string mot = "";
   // cin >> mot;
   // cout << codagev(text, mot) << "\n";
   // cout << jolitexte(decodagev(text, mot)) << "\n" ;

   // test du décodage automatique avec vigenère
   // cout << decodage_automatique_v(text) << "\n";
   // cout << jolitexte(decodagev(text, decodage_automatique_v(text))) << "\n";

   // test de l'analyse de text :
   // cout << analyse(text) << "\n";
   // vector<int> alphabet;
   // analyse(text, alphabet);
   // for(int i = 0; i < 26; i++)
   //    cout << char(i + 65) << " : " << alphabet[i] << "\n";

   // test de la conversion vers d'autre bases :
   // int nb = 0, base = 0, base2 = 0;
   // cin >> nb >> base >> base2;
   // cout << nb << " en base " << base << " : " << versAutreBase(nb, base) << "\n";
   // cout << text << " ( en base " << base2 << ") en base 10 : " << versBaseDix(text, base2);

   // unsigned long long int nb = 0;
   // cin >> nb;

   // test des facteurs premiers :
   // vector<int> factpremsn;
   // factprems(nb, factpremsn);
   // for(int i = 0; i < int(factpremsn.size()); i++)
   //    cout << factpremsn[i] << "\n";

   // test des nombres premiers :
   // vector<int> nbsprems;
   // NbsPremsjusquaN(nb, nbsprems);
   // for(int i = 0; i < int(nbsprems.size()); i++)
   //     cout << nbsprems[i] << "\n";


   // test de la suite de fibonnacci
   // for(int i=0; i<47; i++)
   //    cout << fibo(i) << endl;

   // test de l'approximation de farey
   // float nb1 = 0.67485475;
   // cin >> nb1;
   // cout << farey_approximation(nb1, 10000000) << "\n\n\n";
 
   // test de l'approximatin de la racine carré
   // int nb = 0;
   // cin >> nb;
   // cout << approximation_racinecarre(nb, 100) << endl;
   // cout << pow(nb, 1.0/2) << endl;
   
   return EXIT_SUCCESS;
}
