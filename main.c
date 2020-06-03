#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <stdlib.h>
#include "BigInt.h"


#define NIMEN_PITUUS 256        // Nimen pituudelle kokoa
#define ETUNIMEN_PITUUS 20      // Etunimen pituudelle taulukon koko
#define SUKUNIMEN_PITUUS 40     // Sukunimen pituudelle taulukon koko
#define PIN_PITUUS 6           // PIN-koodin pituudelle taulukon koko 4 +1 +1 (rivinvaihto otettava huomioon)
#define IBAN_PITUUS 19          // IBAN-pankkitilinumeron char-taulukon pituus 18+1, 18 plus loppumerkki
#define ASIAKKAIDEN_LKM 5000   // Pankissa olevien asiakkaiden maksimim‰‰r‰ t‰ss‰ versiossa
#define DIGITS_LKM 11           // char-tyyppisen Numerotaulukon koko: 10 + 1, luvut 0-9 + loppumrkki '\0'


typedef struct ci {
  char name[NIMEN_PITUUS];
  char pin[PIN_PITUUS]; 
  char account[IBAN_PITUUS];
  double saldo;  
}CustomerInfo;

// Nimi‰, k‰ytet‰‰n tietokannan t‰ytt‰miseen
// 110 naisen ja 110 miehen etunime‰, yhteens‰ 220
char FirstNames [][ETUNIMEN_PITUUS] = {
// Naiset 110
"Maria",    "Sofia",    "Liisa",  "Matilda",  "Loviisa",  "Johanna", "Stiina", "Kaisa",       "Emilia", "Annikki", 
"Kyllikki", "Marjatta", "Helena", "Kaarina",  "Elisabet", "Inkeri",  "Mirjam", "Hilkka",      "Helvi",  "Eila",
"Anna",     "Aino",     "Aune",   "Kerttu",   "Aili",     "Sirkka",  "Eeva",   "Toini",       "Helmi",  "Irja",
"Martta",   "Tyyne",    "Rauha",  "Taimi",    "Elsa",     "Maire",   "Hilja",  "Lempi",       "Sylvi",  "Elli",
"Anni",     "Alli",     "Arja",   "Kirsti",   "Terttu",   "Liisa",   "Elma",   "Irma",        "Laina",  "Elvi", 
"Saara",    "Katri",    "Saimi",  "Siiri",    "Meeri",    "Lahja",   "Hilma",  "Maija",       "Helli",  "Lyyli",
"Aini",     "Hilda",    "Bertta", "Helga",    "Salme",    "Kaisa",   "Jenny",  "Lea",         "Hanna",  "Eva", 
"Ester",    "Impi",     "Lilja",  "Ilmi",     "Fanny",    "Karin",   "Esteri", "Sanni",       "Salli",  "Hulda",
"Anja",     "Linda",    "Naima",  "Sandra",   "Ingrid",   "Emmi",    "Astrid", "Vilhelmiina", "Ada",    "Edith",
"Mari",     "Hedwig",   "Julia",  "Justiina", "Amanta",   "Eedla",   "Aurora", "Adolfiina",   "Tekla",  "Karolina",
"Henrika",  "Greta",    "Brita",  "Katriina", "Valpuri",  "Alviina", "Ruusa",  "Madilta",     "Agda",   "Josefiina",
// Common English  Names for Girls
"Abigail",  "Alexis",    "Alice",     "Amanada",    "Amber",    "Amy",     "Andrea",   "Angela",      "Ann",      "Ashley",
"Barbara",  "Betty",     "Beverly",   "Betty",      "Beverly",  "Brenda",  "Brittany", "Carol",       "Carolyn",  "Catherine", 
"Cheryl",   "Christina", "Christine", "Cynthia",    "Danielle", "Deborah", "Debra",    "Denise",      "Diana",    "Diane",
"Donna",    "Doris",     "Dorothy",   "Elizabeth",  "Emily",    "Emma",    "Evelyn",   "Frances",     "Gloria",   "Grace",
"Hannah",   "Heather",   "Helen",     "Jacqueline", "Jane",     "Janet",   "Janice",   "Jean",        "Jennifer", "Jessica",
"Joan",     "Joyce",     "Judith",    "Judy",       "Julia",    "Julie",   "Karen",    "Katherine",   "Kathleen", "Kathryn",
"Kayla",    "Kelly",     "Kimberley", "Laura",      "Lauren",   "Linda",   "Lisa",     "Lori",        "Madison",  "Margaret",
"Marie",    "Marilyn",   "Martha",    "Mary",       "Megan",    "Melissa", "Michelle", "Nancy",       "Natalie",  "Nicole", 
"Olivia",   "Pamela",    "Patricia",  "Rachel",     "Rebecca",  "Rose",    "Ruth",     "Samantha",    "Sandra",   "Sara", 
"Sarah",    "Sharon",    "Shirley",   "Stephanie",  "Susan",    "Teresa",  "Theresa",  "Tiffany",     "Victoria", "Virginia", 
// Les prÈnoms de filles francais les plus tendance
"Jade",     "Louise",    "ChloÈ",    "Lina",     "Mila",     "InÈs",    "Ambre",   "Mia",       "LÈna",      "Manon", 
"Juliette", "Lou",       "ZoÈ",      "Lola",     "Agathe",   "Jeanne",  "Lucie",   "»va",       "Nina",      "Romane",
"Inaya",    "Charlotte", "LÈonie",   "Romy",     "Adele",    "Iris",    "Louna",   "Sofia",     "Margaux",   "Luna",  
"ClÈmence", "LÈana",     "Clara",    "»lena",    "Victoire", "Aya",     "Margot",  "Nour",      "Giulia",    "Charlie", 
"Capucine", "Mya",       "Mathilde", "Lana",     "AnaÔs",    "Lilon",   "Alicia",  "ThÈa",      "Gabrielle", "Lya", 
"Yasmine",  "Maelys",    "Assia",    "Apolline", "»lise",    "Alix",    "Emy",     "Lise",      "Lily",      "Lyana", 
"Lisa",     "NoÈmie",    "Marie",    "Roxane",   "Lyna",     "HÈloise", "Candice", "Valentine", "ZÈlie",     "Maya",  
"Soline",   "CÈlia",     "MaÎlle",   "Emmy",     "Faustine", "SalomÈ",  "Lila",    "Alya",      "ThaÔs",     "Constance", 
"MÈlina",   "Livia",     "Amelia",   "OcÈane",   "Sara",
// Miehet 110
"Juho",    "Kalle", "Matti",  "Johan",  "Antti",  "Heikki", "Karl",   "Frans",  "Kustaa", "Pekka",
"August",  "Otto",  "Mikko",  "Jaakko", "Veikko", "Eino",   "Erkki",  "Pentti", "V‰inˆ",  "Martti",
"Toivo",   "Lauri", "Reino",  "Tauno",  "Viljo",  "Vilho",  "Kauko",  "Paavo",  "Arvo",   "Yrjˆ", 
"Eero",    "Olavi", "Aarne",  "Onni",   "Kaarlo", "Niilo",  "Jaakko", "Esko",   "Pauli",  "Sulo",
"Kalle",   "Unto",  "Oiva",   "Leo",    "Arvi",   "Uuno",   "Aimo",   "Urho",   "Armas",  "Johannes", 
"Alpo",    "Mauno", "Ahti",   "Aaro",   "Erik",   "Kalevi", "Osmo",   "Mauri",  "Risto",  "Ilmari", 
"Keijo",   "Jorma", "Nils",   "Heimo",  "Taisto", "Aarre",  "Helge",  "Teuvo",  "Kaino",  "Jouko",
"Voitto",  "Frans", "Aulis",  "Hugo",   "Veli",   "Olli",   "Paul",   "Lars",   "Sven",   "Allan",
"Kalervo", "Tuure", "Gunnar", "Hannes", "Simo",   "Emil",   "Elis",   "Urpo",   "Einar",  "Aatos",
"Bror",    "Toimi", "Eelis",  "Seppo",  "Leevi",  "≈ke",    "Veijo",  "Vieno",  "Sakari", "Kosti",
"Heino",   "Timo",  "Pertti", "Ensio",  "Kurt",   "Tuomas", "Arvid",  "Edvin",  "Voitto", "Alexander",
// Common American Names for Boys
"Aaron",   "Adam",     "Alan",    "Albert",  "Andrew",  "Anthony", "Arthur",  "Austin",    "Benjamin",    "Billy",
"Bobby",   "Brandon",  "Brian",   "Bruce",   "Bryan",   "Carl",    "Charles", "Christian", "Christopher", "Daniel",
"David",   "Dennis",   "Donald",  "Douglas", "Dylan",   "Edward",  "Eric",    "Ethan",     "Euygene",     "Frank",
"Gabriel", "Gary",     "George",  "Gerald",  "Gregory", "Harold",  "Harry",   "Henry",     "Jack",        "Jacob",
"James",   "Jason",    "Jeffrey", "Jeremy",  "Jerry",   "Jesse",   "Joe",     "John",      "Johnny",      "Jonathan",
"Jordan",  "Jose",     "Joseph",  "Joshua",  "Juan",    "Justin",  "Keith",   "Kenneth",   "Kevin",       "Kyle",
"Larry",   "Lawrence", "Logan",   "Louis",   "Mark",    "Matthew", "Michael", "Nathan",    "Nicholas",    "Noah",
"Patric",  "Paul",     "Peter",   "Philip",  "Ralph",   "Randy",   "Raymond", "Richard",   "Robert",      "Roger",
"Ronald",  "Ray",      "Roy",     "Russell", "Ryan",    "Samuel",  "Scott",   "Sean",      "Stephen",     "Steven", 
"Terry",   "Thomas",   "Timothy", "Tyler",   "Vincent", "Walter",  "Wayne",   "William",   "Willie",      "Zachary",
// Modern American Names for Boys
"Austin",    "Biff",    "Bo",        "Bode",    "Booker",     "Braylen",  "Bronx",  "Brooklyn", "Bryson",  "Bubba",
"Bud",       "Buster",  "Cade",      "Cash",    "Charleston", "Cherokee", "Colt",   "Colton",   "Cord",    "Caro",
"Dakota",    "Dallas",  "Dash",      "Dax",     "Daxton",     "Denali",   "Denzel", "Drake",    "Duke",    "Easton", 
"Ellington", "Gatsby",  "Gunner",    "Hakan",   "Hendrix",    "Hiawatha", "Holden", "Houston",  "Huck",    "Huckleberry", 
"Hudson",    "Ike",     "Jace",      "Jase",    "Jax",        "Jaxton",   "Jayden", "Jazz",     "Jericho", "Jeter", 
"Jett",      "Justice", "Kaiden",    "Kayden",  "Kody",       "Kylo",     "Kymani", "Lakota",   "Lamar",   "Landry",
"Langston",  "Lashawn", "Lebron",    "Lincoln", "Maverick",   "Memphis",  "Mojave", "Montana",  "Nolan",   "Peyton", 
"Poe",       "Rancher", "Raylan",    "Reno",    "Reo",        "Rocky",    "Rowdy",  "Ryder",    "Ryker",   "Saint",
"Satchel",   "Sawyer",  "Shane",     "Sir",     "Sky",        "Spike",    "Steel",  "Stetson",  "Stone",   "Striker",
"Tahoe",     "Taos",    "Tennessee", "Teton",   "Tex",        "Thoreau",  "Tiger",  "Tip",      "Tripp",   "Tucson", 
"West",      "Westin",  "Wilder",    "Yancey",  "Yosemite",   "Yuma",     "Zayden",
// Le top 20-100 des prÈnoms de garÁon franÁais
"Gabriel", "RaphaÎl", "LÈo",     "Jules",    "Lucas",  "MaÎl",    "Hugo",     "Liam",    "Tom",       "Gabin", 
"Sacha",   "Nolan",   "Mohamed", "ThÈo",     "NoÈ",    "Victor",  "Martin",   "Mathis",  "TimÈo",     "Enzo",
"Eden",    "Axel",    "Antoine", "LÈon",     "Marius", "Robin",   "Valentin", "ClÈment", "Baptiste",  "Tiago", 
"Rayan",   "Samuel",  "Amir",    "Augustin", "NaÎl",   "Maxime",  "Gaspard",  "Eliott",  "Alexandre", "Isaac", 
"MathÈo",  "Yanis",   "»van",    "Simon",    "Malo",   "Nino",    "Marceau",  "Kylian",  "Ibrahim",   "Imran",
"Ayden",   "Lenny",   "Camille", "Lyann",    "Kais",   "Oscar",   "Naim",     "Sohan",   "CÙme",      "Milo", 
"Noa",     "Ilyes",   "Noam",    "Diego",    "IsmaÎl", "LÈandre", "Soan",     "Mathys",  "Alexis",    "Lorenzo", 
"Esteban", "Owen",    "Youssef", "Ilyan",    "Adrien", "Ayoub",   "Ali",      "Adem",    "Wassim",    "Logan", 
"Sandro",  "Pablo",   "Antonin", "Benjamin", "Noham",  "Kenzo"
};

// Sukunimet
char LastNames [][SUKUNIMEN_PITUUS] = {
"M‰‰tt‰",     "Kokko",      "Karhu",      "Rautio",     "Autio",      "Repo",        "Huotari",     "Varis",        "Kurki",       "Puhakka", 
"Tikka",      "R‰ty",       "Kuisma",     "J‰ntti",     "Tervo",      "Ahokas",      "K‰rki",       "Sepp‰",        "Rossi",       "M‰enp‰‰", 
"Uusitalo",   "Sillanp‰‰",  "J‰rvenp‰‰",  "Lehtim‰ki",  "V‰lim‰ki",   "Kivim‰ki",    "L‰hteenm‰ki", "Myllym‰ki",    "Hautam‰ki",   "Kankaanp‰‰", 
"Ylitalo",    "Kiviniemi",  "Alatalo",    "Peltoniemi", "Palom‰ki",   "Keskitalo",   "Haapaniemi",  "Riihim‰ki",    "Koivuniemi",  "Kujanp‰‰",
"Virtanen",   "Korhonen",   "M‰kinen",    "Nieminen",   "H‰m‰l‰inen", "Laine",       "M‰kel‰",      "Koskinen",     "J‰rvinen",    "Lehtonen",
"Heikkinen",  "Lehtinen",   "Salminen",   "Saarinen",   "Heinonen",   "Salonen",     "Niemi",       "Turunen",      "Tuominen",    "Heikkil‰",
"Laitinen",   "Rantanen",   "Jokinen",    "Salo",       "Kinnunen",   "Karjalainen", "Mattila",     "Lahtinen",     "Savolainen",  "Ahonen",
"Aaltonen",   "Lepp‰nen",   "Miettinen",  "Laaksonen",  "Ojala",      "V‰is‰nen",    "Hiltunen",    "Leinonen",     "Pitk‰nen",    "Laakso",
"Hakala",     "Kallio",     "Manninen",   "R‰s‰nen",    "Hirvonen",   "Lehto",       "Toivonen",    "Anttila",      "Peltonen",    "Nurmi",
"Koivisto",   "Aalto",      "Mustonen",   "H‰nninen",   "Pulkkinen",  "Partanen",    "Sepp‰l‰",     "Rantala",      "Lappalainen", "Kettunen",
"Moilanen",   "Suominen",   "Saimi",      "Kauppinen",  "Niemel‰",    "Lahti",       "Huttunen",    "Saari",        "Sepp‰nen",    "Oksanen", 
"K‰rkk‰inen", "Kemppainen", "Ahola",      "Koponen",    "Ikonen",     "Halonen",     "Vainio",      "Pesonen",      "Nurminen",    "Vuorinen",
"Mikkonen",   "Peltola",    "Aho",        "Koskela",    "Immonen",    "Mikkola",     "Heiskanen",   "Heino",        "Niskanen",    "Rissanen",
"Honkanen",   "Koski",      "Kokkonen",   "Leino",      "Karppinen",  "Harju",       "M‰ki",        "J‰‰skel‰inen", "Rajala",      "Rautiainen",
"Lindholm",   "Johansson",  "Nyman",      "Lindstrˆm",  "Karlsson",   "Lindroos",    "Lindqvist",   "Andersson",    "Eriksson",    "Lindberg",
"Helenius",   "Helin",      "Blomqvist",  "Lindfors",   "Lindgren",   "Eklund",      "Nylund",      "Nyberg",       "Jansson",     "Holm", 
"Backman",    "Henriksson", "Mattson",    "Holmberg",   "Holmstrˆm",  "Sjˆblom",     "Berg",        "Grˆnroos",     "Forsman",     "Sundstrˆm", 
"Nordstrˆm",  "Nystrˆm",    "Friman",     "Wikstrˆm",   "Vesterlund", "Ekman",       "Ekholm",      "NygÂrd",       "Nyholm",      "Forsstrˆm", 
"Sandberg",   "Grˆnlund",   "Helander",   "Bjˆrklund",  "Siren",      "Lind",        "Bergman",     "Selin",        "Sˆderlund",   "Hellsten", 
"SirÈn",      "Grˆnholm",   "Hellman",    "Lˆnnqvist",  "Sundqvist",  "Snellman",    "Stenberg",    "Vikman",       "Sundberg",    "Sˆderholm", 
"Sandstrˆm",  "Fagerstrˆm", "÷hman",      "Lamberg",    "Nordman",    "Malmberg",    "Wallenius",   "Nordlund",     "Blom",        "Sjˆberg", 
"Lindell",    "Roos",       "Pettersson", "Nikander",   "Sundell",    "Bergstrˆm",   "Sjˆholm",     "Linden",       "Strˆm",       "Ahlgren", 
"Lindeman",   "Nummelin",   "Kajander",   "B‰ckman",    "≈berg",      "Vikstrˆm",    "Malin",       "Blomberg",     "Ek",          "Granlund",
"Westerholm", "Ekstrˆm",    "Sˆderstrˆm", "Lundberg",   "Osterlund",  "Bjˆrkman",    "Forsberg",    "Malm",         "Wallin",      "Nordberg",
// Common family names in the USA
"Smith",     "Johnson", "Williams", "Jones",    "Brown",     "Davis",    "Miller",    "Wilson",     "Moore",     "Taylor",
"Anderson",  "Thomas",  "Jackson",  "White",    "Harris",    "Thompson", "Garcia",    "Martinez",   "Robinson",  "Clark",
"Lewis",     "Lee",     "Walker",   "Hall",     "Allen",     "Young",    "Hernandez", "King",       "Wright",    "Lopez", 
"Hill",      "Scott",   "Green",    "Adams",    "Baker",     "Gonzales", "Nelson",    "Carter",     "Mitchell",  "Perez",
"Roberts",   "Turner",  "Phillips", "Campbell", "Parker",    "Evans",    "Edwards",   "Collins",    "Stewart",   "Sanchez",
"Morris",    "Rogers",  "Reed",     "Cook",     "Morgan",    "Bell",     "Murphy",    "Bailey",     "Rivera",    "Cooper", 
"Richardson", "Cox",    "Howard",   "Ward",     "Torres",    "Peterson", "Gray",      "Ramirez",    "James",     "Watson",
"Brooks",     "Kelly",  "Sanders",  "Price",    "Bennett",   "Wood",     "Barnes",    "Ross",       "Henderson", "Coleman",
"Jenkins",    "Perry",  "Powell",   "Long",     "Patterson", "Hughes",   "Flores",    "Washington", "Butler",    "Simmons",
"Foster",     "Bryant", "Griffin",  "Diaz",     "Hayes",     "Myers",    "Ford",      "Hamilton",   "Graham",    "Sullivan",
// Liste des noms de famille les plus courants en France
"Martin",    "Bernard", "Thomas",   "Petit",     "Robert",    "Richard",    "Durand",   "Dubois",      "Moreau",     "Laurent",
"Simon",     "Michel",  "Lefebvre", "Leroy",     "Roux",      "David",      "Bertrand", "Morel",       "Fournier",   "Girard",
"Bonnet",    "Dupont",  "Lambert",  "Fontaine",  "Rousseau",  "Vincent",    "Muller",   "Lefevre",     "Faure",      "Andre",
"Mercier",   "Blanc",   "Guerin",   "Boyer",     "Garnier",   "Chevalier",  "FranÁois", "Legrand",     "Gauthier",   "Garcia", 
"Perrin",    "Robin",   "Clement",  "Morin",     "Nicolas",   "Henry",      "Roussel",  "Mathieu",     "Gautier",    "Masson", 
"Marchand",  "Duval",   "Denis",    "Marie",     "Lemaire",   "Noel",       "Meyer",    "Dufour",      "Meunier",    "Brun",
"Blanchard", "Giraud",  "Joly",     "Riviere",   "Lucas",     "Brunet",     "Gaillard", "Barbier",     "Arnaud",     "Martinez", 
"Gerard",    "Roche",   "Renard",   "Schmitt",   "Roy",       "Leroux",     "Colin",    "Vidal",       "Caron",      "Picard", 
"Roger",     "Fabre",   "Aubert",   "Lemoine",   "Renaud",    "Dumas",      "Lacroix",  "Olivier",     "Philippe",   "Bourgeois", 
"Pierre",    "Benoit",  "Rey",      "Leclerc",   "Payet",     "Rolland",    "Leclercq", "Guillaume",   "Lecomte",    "Lopez", 
"Jean",      "Dupuy",   "Guillot",  "Hubert",    "Berger",    "Carpentier", "Sanchez",  "Dupuis",      "Moulin",     "Louis",
"Deschamps", "Huet",    "Vasseur",  "Perez",     "Fleury",    "Royer",      "Klein",    "Jacquet",     "Adam",       "Paris", 
"Poirier",   "Marty",   "Aubry",    "Guyot",     "Carre",     "Charles",    "Renault",  "Charpentier", "Menard",     "Maillard",
"Baron",     "Bertin",  "Bailly",   "Herve",     "Schneider", "Fernandez",  "Le Gall",  "Collet",      "Leger",      "Bouvier", 
"Julien",    "Prevost", "Millet",   "Perrot",    "Daniel",    "Le Roux",    "Cousin",   "Germain",     "Breton",     "Besson",
"Langlois",  "Remy",    "Le Goff",  "Pelletier", "Leveque",   "Perrier",    "Leblanc",  "Barre",       "Lebrun",     "Marchal",
"Weber",     "Mallet",  "Hamon",    "Boulanger", "Jacob",     "Monnier",    "Michaud",  "Rodriguez",   "Guichard",   "Gillet", 
"Etienne",   "Grondin", "Poulain",  "Tessier",   "Chevallier", "Collin",    "Chauvin",  "Da Silva",    "Bouchet",    "Gay",
"Lemaitre",  "Benard",  "Marechal", "Humbert",   "Reynaud",    "Antoine",   "Hoarau",   "Perret",      "Barthelemy", "Cordier", 
"Pichon",    "Lejeune", "Gilbert",  "Lamy",      "Delaunay",   "Pasquier",  "Cartier",  "Laporte"
};

// LUKUTAULUKKO
char Digits[DIGITS_LKM] = "0123456789";


void luepois(void);  // N‰pp‰imistˆpuskurin tyhjent‰j‰

int areDigits(char *, int);  // Ovatko annetut merkit numeroita
char* mystrcat(char* dest, char* src);  // oma strcat -funktio, napattu internetist‰, hieman erilainen normaaliin

int valitseToiminto(char* strNimi); // Valitse -p‰‰valikko

// Arvotaan asiakkaita ja samalla kysyt‰‰n k‰ytt‰j‰n nimi. 
// Kun nimmi lis‰t‰‰n tietuetaulukkoon, annetaan samalla PIN-koodi,
// jolla voi sitten tehd‰ tililt‰ nostoja. Tilille arvotaan jonkinlainen saldo.
void allotRecords( CustomerInfo custInfo[], int* nAdd); // arvotaan asiakkaita, joilla on pankkitili

// Arvotaan nelinumeroinen PIN-luku, j‰rjestelm‰ antaa PIN-koodin
void allotPin (char* strPin);

// j‰rjestelm‰ antaa IBAN-tilinumeron
void giveAccount(char* strAccount, int nAdd);

// muuta tavallinen tilinumero IBAN-muotoon
void transformToIBAN (char* strAccount);
// poista merkkijonosta strString osamerkkijono strSub
void removeSubstr (char *strString, char *strSub);

// muunna heksadesimaaliluku desimaaliluvuksi
// toimii vain pienill‰ desimaaliluvuilla
// mutta riitt‰‰ t‰h‰n
int hexadecimalToDecimal( char hexVal[]);

// Arvotaan saldo
double allotSaldo(void);

// Etsit‰‰n, onko asiakkaan nimi tietokannassa
int findCustomerByStr( CustomerInfo custInfo[], char* strName, int nLength);

// Etsit‰‰n, vastaako asiakkaan nimi ja PIN-koodi toisiaan
int findPinByStr( CustomerInfo custInfo[], char* strName, char* strPin, int nLength);

void teeOtto(CustomerInfo custInfo[], char* strNimi, char *strPin, int nLength);       // Tehd‰‰n asiakkaan tililt‰ otto
void tulostaSaldo(CustomerInfo custInfo[], char* strNimi, char* strPin, int nLength);  // Tulostetaan asiakkaan saldo
void tulostaTilitapahtumat(CustomerInfo custInfo[], char* strNimi, char* strPin, int nLength); // Tulosta asiakkaan tilitapahtumat
void lataaPuheaikaa(CustomerInfo custInfo[], char* strNimi, char* strPin, int nLength); // Lataa asiakkaan puhelinliittym‰‰n rahaa
void valitseTili(CustomerInfo custInfo[], char* strNimi, char* strPin, int nLength);    // Valitse tili (tass‰ ei k‰ytˆss‰)

int main(int argc, char *argv[]) {
	
	printf("\nPankkiautomaattisimulaatio - Mika Huttunen\n\n");
   
   printf("Talla ohjelmalla simuloidaan pankkiautomaattia.\n\
Ohjelma generoi pankin asiakkaita ja n‰ille IBAN-muotoiset tilinumeron ja saldon.\n\
Toteutuksessa on kaytetty c-ohjelmointikielta.\n\n");

char strStopName[]="POIS";      // STOP-merkki, nimi jolla p‰‰st‰‰n ohjelmaluupista pois
char strNimi [NIMEN_PITUUS]; 
char strPin [PIN_PITUUS] = {0};
int nPinSize = 0;
char strTestPin[5] ="2718";  // Testi-PIN, jolla testataan ohjelman toimivuutta
char strTestName[] = "Bill Bates"; // Testi-NIMI, jolla testataan ohjelman toimivuutta
static int nAdd = 0;               // Tilinumeroiden kasvattamiseen


// Asiakasrekisteri
CustomerInfo rekisteri[ASIAKKAIDEN_LKM];  // Pankissa olevien asiakkaiden lkm
// t‰ytet‰‰n asiakasrekisteri
allotRecords(rekisteri, &nAdd);

int nValinta = 0;

do {
   printf("\n\nPANKKIAUTOMAATTI");
   printf("\nKun haluat poistua, anna nimeksi \"POIS\".");
   printf( "\nTervetuloa!\nAnna nimesi, ole hyva (SYOTA KORTTI) > ");
   fgets( strNimi, NIMEN_PITUUS, stdin);
   // Jos syˆtetty merkkijono oli lyhyempi kuin mit‰ 
   // nimimuuttujaan mahtuu, on '\n' eli enter/return
   if ( strNimi[strlen(strNimi)-1] == '\n'){
         strNimi[strlen(strNimi)-1] = '\0'; // loppumerkki oikeaan paikkaan
   }     
   else
      luepois();  // tyhjennet‰‰n lukupuskuri
   
   if ( strcmp( strNimi, strStopName ) == 0)    
      printf("\nNakemiin!");
   else if ( findCustomerByStr(rekisteri, strNimi, nAdd+1) == -1){
      
      continue;
   }
   else
      printf("\nTervetuloa kayttamaan pankkiautomaattia %s.\n", strNimi);
   
   if ( strcmp( strNimi, strStopName ) != 0 ){ // Ei tehd‰ luuppia, jos halutaan heti keskeytt‰‰
   
    do {
       printf("\nNappaile tunnusluku\nSuojaa tunnuslukusi\nlopuksi paina ENTER\n\
   4-numeroinen PIN-koodi > ");
       fgets(strPin, PIN_PITUUS, stdin);
       // Jos syˆtetty merkkijono oli lyhyempi kuin mit‰ 
       // nimimuuttujaan mahtuu, on '\n' eli enter/return
      if ( strPin[strlen(strPin) -1] == '\n' ){
         strPin[strlen(strPin) -1] = '\0';  // loppumerkki oikeaan paikkaan
         nPinSize = strlen(strPin) -1;
      }
      else
        luepois();
        
      printf("PIN (tarkistus) : %s", strPin);
      
    }
    while(!areDigits(strPin, nPinSize) );
    
    if ( findPinByStr(rekisteri, strNimi, strPin, nAdd+1) == -1 ){
       continue;
    }
  
     // Tullaan p‰‰valikkoon
     // Toteutetaan switch-case -rakenteella
     nValinta = valitseToiminto(strNimi);
  
     switch (nValinta ){
        case 0:
           printf("\nSTOP\nLopetetaan...\n");
           break;
        case 1: 
           teeOtto(rekisteri, strNimi, strPin, nAdd +1);
           break;
        case 2:
           tulostaSaldo(rekisteri, strNimi, strPin, nAdd +1);
           break;
        case 3: 
           tulostaTilitapahtumat(rekisteri, strNimi, strPin, nAdd +1);
           break;
        case 4:
           lataaPuheaikaa(rekisteri, strNimi, strPin, nAdd +1);
           break;
        case 5:
           valitseTili(rekisteri, strNimi, strPin, nAdd +1);
           break;
        default:
           printf("\nPalataan alkunayttoon");
           break;       
     
     }
  } // ulompi if
  
   
} while ( strcmp(strNimi, strStopName) != 0 );  // P‰‰luuppi 
	
	return 0;
}

void luepois(void){
   while (getc(stdin) != '\n' );
}

int areDigits(char* table, int nSize){
   int bDigits = 0;
   int i=0;
   
   for (i=0; i < nSize; i++ )
   {
      if ( !isdigit(table[i]) ){
         printf("\nVaara PIN-koodi. Annoit muita kirjaimia kuin numeroita!\n");
         bDigits = 0;
         break;
      }
      else
        bDigits = +1;
   }
   
   return bDigits;
}

// oma strcat -toiminto, koodi napattu internetist‰
// palautetaan osoitin uuden, pidemm‰n stringin per‰‰n
char* mystrcat( char* dest, char* src){
   while (*dest) dest++;
   while ( *dest++ = *src++);
   return --dest;
}


int valitseToiminto(char* strNimi){
   int nChoice;
   int nStatus=0;
   char chMki;
   char chMerkki;
   
   
   printf("\nTervetuloa %s!\n", strNimi);
   printf("\nVALITSE\nVoit lopettaa antamalla luvun 0\n\n");
   printf("0) LOPETUS\n");
   printf("1) OTTO\n");
   printf("2) SALDO\n");
   printf("3) TAPAHTUMAT\n");
   printf("4) LIITTYMAN LATAUS\n   PUHEAIKA\n");
   printf("5) TILIN VALINTA\n");
   printf("\n\nAnna valintasi > ");
   
   while ( ( nStatus = scanf("%d%c", &nChoice, &chMki) ) == 0 || 
           ( nStatus == 2 && chMki != '\n') ||
           ( nChoice < 0 || nChoice > 5) ){
              
              if ( nChoice < 0 || nChoice > 5 ){
                 printf("\nAntamaasi lukua ei ole valikossa!\n");
                 printf("\nAnna valintasi (0-5) > ");
              }
              else {
                 while ( ( chMerkki = getchar() ) != '\n');
                 printf("\nAnnoit roskan %c\n",  chMerkki);
                 printf("\nAnna valintasi (0-5) > ");
              }
           }
   
   return nChoice;
}

// arvotaan asiakkaita, joilla on pankkitili
// Lis‰t‰‰n myˆs k‰ytt‰j‰n tili, koska muuten k‰ytt‰j‰ ei p‰‰se tiliins‰ k‰siksi
void allotRecords( CustomerInfo custInfo[], int* nAdd){
   int i=0;
   const int nEnd = 4998;  // Kuvitteellisen pankkimme asiakasm‰‰r‰
                           // T‰h‰n lis‰t‰‰n k‰ytt‰j‰n tili
   char strFirstName[ETUNIMEN_PITUUS]; // etunimi
   char strLastName[SUKUNIMEN_PITUUS]; // sukunimi
   char strName[NIMEN_PITUUS];         // etunimi + sukunimi
   char strPin[PIN_PITUUS];            // merkkitaulukko 4-numeroiselle PIN_koodille
   
   char strIBAN[IBAN_PITUUS];       // IBAN TILINUMERO
   
   double dblSaldo = 0.0;
   
   // kuinka monta etunime‰ etunimitaulukossa
   int nFirstNames = sizeof(FirstNames) / sizeof((FirstNames)[0]);
   // testi: montako etunime‰
   printf( "\nEtunimia %d kpl", nFirstNames);
   // kuinka monta sukunime‰ on sukunimitaulukossa
   int nLastNames = sizeof(LastNames) / sizeof ( (LastNames)[0] );
   // testi: montako sukunime‰
   printf("\nSukunimia %d kpl", nLastNames);
   
   
   
   // alustetaan, tai "annetaan siemen"  satunnaislukugeneraattori
   srand( (long) time(0));
   
   // Kirjoitetaan CSV-tiedostoon     
   FILE* csvFile = fopen("names.csv","w");    
   fprintf(csvFile,"%s\n", "name");
   FILE* csvFileII = fopen("accounts.csv","w");   
   fprintf(csvFileII, "%s,%s\n", "tilitunnus", "saldo");          
   for ( i=0; i < nEnd; i++ )
   {
      strName[0] = '\0';            // tyhjennet‰‰n strName -merkkijonotaulukko
      // char* pName = strName;
      strFirstName[0] = '\0';  // tyhjennet‰‰n strFirstName merkkijonotaulukko
      strcpy(strFirstName , FirstNames[rand() % nFirstNames]); // arvotaan satunnainen etunimi
      strcpy( strName, strFirstName); // kopioidaan etunimi Nimeen  
      //pName = mystrcat( pName, strFirstName);    
      strcat( strName, " ");  // lis‰t‰‰n etunimen j‰lkeen v‰li          
     // pName = mystrcat(pName, " ");            
       strLastName[0] = '\0';                  // tyhjennet‰‰n strLastName -merkkijonotaulukko
      strcpy(strLastName, LastNames[rand() % nLastNames]);    // arvotaan satunnainen sukunimi     
      strcat(strName, strLastName); // kopioidaan sukunimi Nimeen
      // pName =mystrcat(pName, strLastName); 
             
      // strcpy(custInfo[i].name, pName);  // tietueen NAME -kentt‰
      strcpy( custInfo[i].name, strName); 
      
      // arvotaan 4-numeroinen PIN-koodi
      strPin[0] = '\0';  // tyhjennet‰‰n strPin
      // t‰ytet‰‰n strPin nelj‰ numeroa sis‰lt‰v‰ll‰ merkkijonolla
      allotPin(strPin);
      strPin[4] = '\0';  // viides merkki merkkijonon loppu
      strcpy(custInfo[i].pin, strPin);
      
      // Annetaan tilinumero
      strIBAN[0] = '\0';  // tyhjennet‰‰n strIBAN
      giveAccount(strIBAN, (*nAdd));
      strcpy(custInfo[i].account, strIBAN);
      
      // arvotaan saldo
      custInfo[i].saldo = allotSaldo();
     
      // testi: arvottu nimi
      printf( "\n[%4d] %-24s (%4s) [%18s] %.2lf EURO", i+1, custInfo[i].name, custInfo[i].pin, custInfo[i].account, custInfo[i].saldo);
      fprintf(csvFile,"%s\n", custInfo[i].name);
      fprintf(csvFileII,"%s,%.2lf\n", custInfo[i].account, custInfo[i].saldo);
      (*nAdd)++;      
   }
   fclose(csvFile);
   fclose(csvFileII);
   strName[0] = '\0'; // Tyhjennet‰‰n strName-merkkijono
   printf("\n\n\nOlette tulossa korttiasiakkaaksi pankkiimme Automatia. \nAntakaa nimenne ja painakaa sitten ENTER > ");
   fgets ( strName, NIMEN_PITUUS, stdin);
   /* Jos syˆtetty merkkijono oli lyhyempi kuin mit‰ nimimuuttujaan mahtuu,
      on '\n' el enter/return merkki viimeisen‰. Laitetaan nimen j‰lkeen 
      loppumerkki oikeaan paikkaan.
   */
   if ( strName[strlen(strName) -1] == '\n')
      strName[strlen(strName) -1] = '\0';
   else
     luepois();
   
   // Lis‰t‰‰n nimi tietokantaan
   strcpy(custInfo[i].name, strName);
   // Annetaan tiedote asiakkaalle tilinumerosta ja PIN-luvusta
   printf("\nTietosi on tallennettu tietokantaan, hyva %s.", custInfo[i].name);
   printf("\nPankkijarjestelma on generoinut Teille tilinumeron ja pankkikorttinne PIN-koodin.");
   // Generoidaan tilinumero
   strIBAN[0] = '\0'; // tyhjennet‰‰n strIBAN
   giveAccount( strIBAN, (*nAdd)); 
   // Lis‰t‰‰n tilinumero 
   strcpy( custInfo[i].account, strIBAN);
   // Generoidaan PIN-koodi
   strPin[0] = '\0';  // tyhjennet‰‰n strPIN
   allotPin(strPin);
   // Lis‰t‰‰n PIN-koodi
   strcpy( custInfo[i].pin, strPin);
   // Generoidaan tilille rahaa!
   custInfo[i].saldo = allotSaldo();
   printf("\nAlla ovat tietonne. Laittakaa PIN-koodinne muistiin. Voitte nyt alkaa tehd‰ nostoja uudella kortillanne.\n");
   printf("\n%6s %-24s %-6s %-20s %-8s", "As.nro", "Nimi", "PIN", "IBAN-tilinumero", "Saldo" );
   printf( "\n[%4d] %-24s %-6s %-20s %.2lf EURO", i+1, custInfo[i].name, custInfo[i].pin, custInfo[i].account, custInfo[i].saldo);
   
      
} // END OF allotRecords

// Arvotaan nelinumeroinen PIN-luku
void allotPin (char* strPin){
   const int nEnd =4;
   int i=0;  
   
   for (i=0; i < nEnd; i++){      
      strPin[i] = Digits[(rand() % (DIGITS_LKM -1) )];
   } 
} // END OF allotPin

// j‰rjestelm‰ antaa IBAN-tilinumeron
// strAccount on asiakkaan tilinumero 
// nAdd on numero joka kasvaa yhdell‰ aina uuden asiakkaan ollessa kyseess‰
void giveAccount(char* strAccount, int nAdd){
   const char strBase[] = "648413-"; // kuvitteellisen pankkimme kantaluku
                                     // T‰m‰ merkkijono on kaikkien kuvitteellisen pankin asiakkaiden tilinumeron alussa
   char strOrdAccount[15];           // Tavallinen tili
   char strAccEnd[6];                // Tilin loppuosa, jota kasvatetaan                  
   
   const int nBase = 57000;          // Tilinumero, jota kasvatetaan; ALKUARVO
   int nNum = nBase + nAdd;          // Yksilˆllinen tilinumeron loppuosa
   
   /*
   Muistis‰‰ntˆ:
   const char *str = "12345";
   int x;
   sscanf(str, "%d", &x);
   printf("\nValue of x: %d", x);
   */
                                     
   // Muutetaan yksilˆllinen loppuosa merkkijonoksi
   itoa(nNum, strAccEnd, 10);
   
   // testi
  // printf("\n %s", strAccEnd);                                  
   
   // Tavallinen tIlinumero
   strcpy(strOrdAccount, strBase);
   strcat(strOrdAccount, strAccEnd);   
   // testi
  // printf( "\n %s", strOrdAccount);
  strcpy(strAccount, strOrdAccount);
  transformToIBAN(strAccount);
}

// muuta tavallinen tilinumero IBAN-muotoon
// IBAN-muoto Wikipedian sivulta https://fi.wikipedia.org/wiki/IBAN
void transformToIBAN (char* strAccount){
    // Oletetaan, ett‰ parametrina tuleva taulu strAccount on tavallisessa BBAN-muodossa
   // esimerkiksi 648413-61997
   // Poistetaan v‰liviiva, erotinmerkki "-"
   const int nBBAN = 15;
   const int nStart = 8;
   const int nEnd = 7;
   const int nIBAN = 19;       // IBAN-taulukon koko
   const int nIBANapu = 21;    // Aputaulukko IBAN-taulukon koko + 2 
   char strBBAN [nBBAN];       // 14-merkkinen BBAN-numero, 14 +1  
   int nBBANLen = 0;
   char strStart[nStart];      // alkumerkit ennen nollia
   int nStartLen = 0;
   char strEnd[nEnd];          // nollien j‰lkeiset merkit    
   int nEndLen =0; 
   char  chFirstChar;          // Tilinumeron ensimm‰inen numeromerkki
   int nZeroCount =0;          // Nollien lukum‰‰r‰    
   char strIBAN [nIBAN];       // Haluttu IBAN-tilinumero, koko 18 + 1
   char strIBANapu[nIBANapu];  // aputaulukko
   char strIBANtemp[nIBANapu]; // toinen aputaulukko
   int nCountryNumOne = 0;     // Maanumerosta laskettava luku
   int nCountryNumTwo = 0;     // Maanumerosta laskettava toinen
   char* pch;                  // apuosoitinmuuttuja
   char chApu;                 // apumerkkimuuttuja
   char strApu[2];             // apumuuttuja 2 merkin taulukko
   char strApuII[3];           // apumuuttuja 3 merkin taulukko
   
   int nCheckID = 0;           // Tarkistusnumero
   const char strCountryID[] ="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"; 
   
   // BigInt -muuttujia ylivuodon kiert‰miseksi
   // ja tarkistusnumeron laskemiseksi
   char strBufferOne[256];
   char strBufferTwo[256];
   char strBufferThree[256];
   char strBufferFour[256];
   char strBufferFive[256];
   char strCheckID[256];
   
   // Isot luvut pidet‰‰n 30 words:in rajoissa
   int words = 30;
   
   // Allokoidaan muistia 6 numerolle, kaikki 30 wordsin pituisia
   BigInt_t* number1 = malloc(BigIntWordSize*words);
   BigInt_t* number2 = malloc(BigIntWordSize*words);
   BigInt_t* number3 = malloc(BigIntWordSize*words);
   BigInt_t* number4 = malloc(BigIntWordSize*words);
   BigInt_t* number5 = malloc(BigIntWordSize*words);
   BigInt_t* biCheckID = malloc(BigIntWordSize*words);
   
   int i=0;
   int nLen;
   nLen = strlen(strAccount);
   // testi 
   //  printf("\nstrAccount len: %d\n", nLen);
   
   // Kopioidaan strAccount -merkkijono strBBAN-merkkijonoon, jota t‰ss‰ sitten
   // manipuloidaan
   for ( i=0; i < nLen; i++)
     strBBAN[i] = strAccount[i];   
     
   strBBAN[i] = '\0'; // Laitetaan loppumerkki, kun numerot on k‰yty l‰pi    
    
   // Poistetaan v‰liviiva
   removeSubstr(strBBAN, "-");
   
   nBBANLen = strlen(strBBAN);
   
   // Kun pankkiryhm‰n tunnus (BBAN-tilinumeron ensimm‰inen tai kaksi 
   // ensimm‰ist‰ numeroa) on muu kuin 4 tai 5, lis‰t‰‰n BBAN-numeroon 
   // vasemmalta lukien KUUDENNEN numeron j‰lkeen nollia siten, ett‰
   // tilinumeron pituudeksi tulee  14 numeroa. Mik‰li pankkiryhm‰n
   // tunnus on 4 tai 5, lis‰t‰‰n nollia vasta SEITSEMƒNNEN numeron
   // j‰lkeen.
   
   // BBAN-tilinumeron ensimm‰isen numero
   chFirstChar = strBBAN[0];
   // testi
   // printf("\nEnsimmainen numero: %c\n", chFirstChar);
   
   // Jos BBAN-tilinumeron ensimm‰inen numero ei ole 4 tai 5
   if ( !(chFirstChar == '4' || chFirstChar == '5') ){
      // KUUSI NUMEROA ALKUUN
      for ( i=0; i < 6; i++)
         strStart[i] = strBBAN[i];
      
      nStartLen = strlen(strStart); // Pit‰‰ olla 6
      // tarkistus
      // printf( "\nnStartLen %d\n", nStartLen);
      
      // BBAN-tilinumeron loppunumerot
      for ( i=6; i < nBBANLen; i++)
         strEnd[i-6] = strBBAN[i];
      
      strEnd[i-6] = '\0';
         
      nEndLen = strlen(strEnd);
      // tarkistus
      // printf("\nnEndLen %d\n", nEndLen);
      
   } else{  // tilinumeron ensimm‰inen numero on 4 tai 5
       
       // SEITSEMƒN numeroa alkuun
       for ( i=0; i < 7; i++)
         strStart[i] = strBBAN[i];   
         
        nStartLen = strlen(strStart);  // Pit‰‰ olla 7
        // tarkistus
        // printf("\nnStartLen %d", nStartLen);
        
        for ( i=7; i < nBBANLen; i++)
          strEnd[i-7] = strBBAN[i];
          
        strEnd[i-7] = '\0';
          
        nEndLen = strlen(strEnd);  
        // tarkistus
        // printf("\nnEndLen %d\n", nEndLen);  
   } 
   
   // Nollien lukum‰‰r‰ v‰liss‰
   nZeroCount = nBBAN -1 -nStartLen - nEndLen;
   // printf("\nnZeroCount is %d\n", nZeroCount);
   
   strBBAN[0] = '\0';
   // BBAN-numero
   for ( i=0; i < nBBAN -1 ; i++){
        // Alkuosa
        if ( i < nStartLen )
           strBBAN[i] = strStart[i];
        // NOLLIA v‰liin nZeroCountin verran
        if ( i >= nStartLen && i < nStartLen + nZeroCount ){
           strBBAN[i] = '0';
        }
        if ( i >= nStartLen + nZeroCount ){
           strBBAN[i] = strEnd[i-(nStartLen +nZeroCount)];
        }          
   }
    strBBAN[i] = '\0';   // Loppuun loppumerkki
   
   // tarkistus
   //printf("\nstrBBAN length is %d\n", strlen(strBBAN) );
   
   // Tarkistus
   //for ( i =0; i < nBBAN -1; i++)
   //   printf("%c", strBBAN[i]);
   // strAccount[0] = '\0';
   // for ( i=0; i < nBBAN; i++)
   //   strAccount[i] = strBBAN[i];
   
   // Kopioidaan 14- numeroinen BBAN-tilinumero 
   // 18-numeroiseen strIBANapu- ja strIBANtemp-taulukkoon
    strcpy( strIBANapu, strBBAN);
    strcpy( strIBANtemp, strBBAN);
    
    // Kokonaisen 14-numeroisen BBAN-tilinumeron loppuun liitet‰‰n
    // maatunnus (Suomessa FI) ja kaksi nollaa
    strIBANapu[14] = 'F';  // 15. kirjain 'F'
    strIBANapu[15] = 'I';  // 16. kirjain 'I'
    strIBANapu[16] = '0';  // 17. kirjain merkki 0
    strIBANapu[17] = '0';  // 18. kirjain merkki 0
    
    // Ensimm‰inen maanumero
    chApu = strIBANapu[14];
    strApu[0] = chApu;
    strApu[1] = '\0';
    // Etsit‰‰n chApu:a vastaava indeksinumero lookup-taulukosta
    // c-standardifunktiolla strcspn, joka palauttaa indeksin
    nCountryNumOne = strcspn(strCountryID, strApu);
    // Muutetaan nCountryNumOne merkkijonoksi itoa-funktiolla
    itoa(nCountryNumOne, strApuII, 10);
    // Lis‰t‰‰n merkkijono strIBANtemp-merkkijonoon konkatenaatiofunktiolla strcat
    strcat(strIBANtemp, strApuII);
    strApuII[0] = '\0'; // nollataan strApuII uusiok‰yttˆ‰ varten
    
    
    // Toinen maanumero
    chApu = strIBANapu[15];
    strApu[0] = chApu;
    strApu[1] = '\0';
    // Etsit‰‰n chApu:a vastaava indeksinumero lookup-taulukosta
    nCountryNumTwo = strcspn( strCountryID, strApu);
    // Muutetaan nCountryNumTwo merkkijonoksi itoa-funktiolla
    itoa( nCountryNumTwo, strApuII, 10);
    // Lis‰t‰‰n merkkijono strIBANtemp-merkkijonoon strcat-funktiolla
    strcat( strIBANtemp, strApuII);
    // Lis‰t‰‰n kaksi  nolla-merkki‰ strIBANtemp-merkkijonon loppuun
    strcat( strIBANtemp, "00");
    
    // Muutetaan merkkijonotaulukko kokonaisluvuksi
    // Ylivuodon v‰ltt‰miseksi k‰ytet‰‰n SUURIA LUKUJA 
    // Ilia Sibiryakov:in koodaamia BigInt-funktioita (itse en osannut)
    // 
    // strIBANtemp muutetaan BigInt-luvuksi number1
    BigInt_from_string(words, number1, strIBANtemp);
    // t‰m‰ luku jaetaan luvulla 97
    // muutetaan luku 97 BigInt-luvuksi
    BigInt_from_string(words, number2, "97");
    // jakoj‰‰nnˆs v‰hennet‰‰n luvusta 98
    // muutetaan luku 98 BigInt-luvuksi
    BigInt_from_string(words, number5, "98");
    
    // jaetaan strIBANtemp:in edustama luku luvulla 97
    // saatu jakotulos tallennetaan BigInt-muuttujaan number3
    BigInt_div(words, number1, number2, number3); // t‰t‰ itse asiassa ei tarvita, mutta onpahan nyt mukana
    // Otetaan lukujen number1 ja number 2 jakoj‰‰nnˆs
    BigInt_mod(words, number1, number2, number4);
    
    // V‰hennet‰‰n luvusta number5 jakoj‰‰nnˆs number 4
    // ja tallennetaan tulos BigInt-lukuun biCheckID, joka
    // on haluttu IBAN-tarkistenumero hexadesimaalimuodossa
    BigInt_sub(words, number5, words, number4, words, biCheckID);
    
    // BigInt biCheckID muutetaan hexadesimaalimuotoon
    BigInt_to_hex_string(words, biCheckID, strCheckID);
    
    // Muutetaan hexadesimaali tarkistenumero kokonaisluvuksi
    nCheckID = hexadecimalToDecimal( strCheckID);
    
    // Nollataan apumuuttujat
    strApu[0] = '\0';
    strApuII[0] = '\0';
    // Mik‰li tarkiste on pienempi kuin 10, lis‰t‰‰n etunolla
    if ( nCheckID < 10){
       strApuII[0] = '0';
       itoa(nCheckID, strApu, 10);
       strApuII[1] = strApu[0];
    }
    else
       itoa(nCheckID, strApuII, 10);
    
    // Tˆytetaan valmis IBAN-numero
    // strAccount[0] = '\0';
    // strAccount[0]='F';
    // strAccount[1] = 'I';
    strcpy(strAccount, "FI");      // Alkuun maatunnus
    strcat(strAccount, strApuII);  // Tarkistenumero, 2 MERKKIƒ
    strcat(strAccount, strBBAN);   // Loppunumeron merkkijono, 14 MERKKIƒ
    
}

// Poista merkkijonosta strString osamerkkijono strSub
// strstr- ja strcat-funktioiden avulla
void removeSubstr (char *strString, char *strSub) {
    char *strMatch;
    int nLen = strlen(strSub);
    while ((strMatch = strstr(strString, strSub))) {
        *strMatch = '\0';
        strcat(strString, strMatch+nLen);
    }
}

// Function to convert hexadecimal to decimal 
// toimii vain suhteellisen pienill‰ luvuilla
// ei toimi eritt‰in isojen lukujen tapauksessa
int hexadecimalToDecimal(char hexVal[]) 
{    
    int len = strlen(hexVal); 
      
    // Initializing base value to 1, i.e 16^0 
    int base = 1; 
      
    int dec_val = 0; 
      
    // Extracting characters as digits from last character 
    int i;
    for (i=len-1; i>=0; i--) 
    {    
        // if character lies in '0'-'9', converting  
        // it to integral 0-9 by subtracting 48 from 
        // ASCII value. 
        if (hexVal[i]>='0' && hexVal[i]<='9') 
        { 
            dec_val += (hexVal[i] - 48)*base; 
                  
            // incrementing base by power 
            base = base * 16; 
        } 
  
        // if character lies in 'A'-'F' , converting  
        // it to integral 10 - 15 by subtracting 55  
        // from ASCII value 
        else if (hexVal[i]>='A' && hexVal[i]<='F') 
        { 
            dec_val += (hexVal[i] - 55)*base; 
          
            // incrementing base by power 
            base = base*16; 
        } 
    } 
      
    return dec_val; 
} 


// Arvotaan saldo tilille
double allotSaldo(void){
   double low = 0.0;       // Pienin tilill‰ oleva raham‰‰r‰
   double high = 50000.0;  // Suurin tilill‰ oleva raham‰‰r‰
   double d;
   
   d = (double) rand() / ( (double) RAND_MAX +1);  // Arvotaan satunnaisliukuluku
   
   return (low + d * (high - low) );   // Palautetaan satunnaisesti arvottu saldo
}

// Etsi asiakas
int findCustomerByStr( CustomerInfo custInfo[], char* strName, int nLength){
   int nIndex = 0;  
   int searchFlag = -1; // Jos etsint‰ ei onnistu, palauta -1
   
   for ( nIndex = 0; nIndex < nLength; nIndex++){
      if (strcmp( custInfo[nIndex].name, strName ) == 0){
          printf("\nLoytyi nimen %s perusteella asiakas\n ", custInfo[nIndex].name);
          printf("\n\n%-30s%-6s%-20s%-8s\n", "Nimi", "PIN", "IBAN-tilinumero", "Saldo" );
	       printf("%-30s%-6s%-20s%.2lf\n", custInfo[nIndex].name, custInfo[nIndex].pin, 
          custInfo[nIndex].account, custInfo[nIndex].saldo);  
	       searchFlag = nIndex;
      }
     
   }
   
   if ( searchFlag == -1 )
      printf("\nVIRHE! Ei nimea tietokannassa.");
   
   return searchFlag;
}

// Etsit‰‰n, vastaako asiakkaan nimi ja PIN-koodi toisiaan
int findPinByStr( CustomerInfo custInfo[], char* strName, char* strPin, int nLength){
   int nIndex = 0;  
   int searchFlag = -1; // Jos etsint‰ ei onnistu, palauta -1
   
   for ( nIndex = 0; nIndex < nLength; nIndex++){
      if (strcmp( custInfo[nIndex].name, strName ) == 0){
          // printf("\nLoytyi nimen %s perusteella asiakas\n ", custInfo[nIndex].name);
          // printf("\n\n%30s )
	       // printf("%s %s [%s, %.2lf]\n", custInfo[nIndex].name, custInfo[nIndex].pin, 
          // custInfo[nIndex].account, custInfo[nIndex].saldo);  
          if ( strcmp(custInfo[nIndex].pin, strPin) == 0 )
	          searchFlag = nIndex;
      }
      
   }
   
   if ( searchFlag == -1 )
      printf("\nVIRHE! PIN-koodi vaarin.");
   
   return searchFlag;
}



// Tehd‰‰n asiakkaan tililt‰ otto
void teeOtto(CustomerInfo custInfo[], char* strNimi, char *strPin, int nLength){
   int nIndex = 0;
   int nSearchFlag = -1;
   double dOrigSaldo = 0;
   double dSaldo = 0;
   double dOtto = 0.0; 
   int nOtto = 0;
   int nChoice = 0;
   int nStatus = 0;
   char chMki;
   char chMerkki;
   
   
   // Etsit‰‰n asiakas
   for ( nIndex = 0; nIndex < nLength; nIndex++){
      if  ( strcmp( custInfo[nIndex].name, strNimi) == 0 &&    // Nimi ja
            strcmp( custInfo[nIndex].pin, strPin)   == 0 )     // PIN-koodi t‰sm‰‰v‰t
          nSearchFlag = nIndex;
   }
   
   dOrigSaldo = custInfo[nSearchFlag].saldo;

   printf("\n\nOTTO\n");
   printf("\n1) 20 euroa\t\t\t\t4) 90 euroa\n" );
   printf("\n2) 40 euroa\t\t\t\t5) 140 euroa\n" );
   printf("\n3) 60 euroa\t\t\t\t6) 240 euroa\n" );
   printf("\n0) Alkuun  \t\t\t\t7) Muu summa\n" );
   
   printf("\nAnna valintasi > ");
     
   while (  ( nStatus = scanf("%d%c", &nChoice, &chMki)) == 0 ||
            ( nStatus == 2 && chMki != '\n' )){
               while ( ( chMerkki = getchar() ) != '\n');
               printf("\nAnnoit roskan %c\n", chMerkki);
               printf("\nAnna kokonaisluku 0-7 > 0 ");
            }
   
   switch ( nChoice ){
      case 0: 
        printf( "\nPoistutaan ...");
        break;
      case 1: 
        dOtto = 20.0;
        if ( dOrigSaldo < dOtto )
           printf("\nTilin saldo ei riita!\n" );
        else{
           dSaldo = dOrigSaldo - dOtto;
           custInfo[nSearchFlag].saldo = dSaldo;
           printf("\nOta kortti.\nNosto onnistui!");
        }
        
        if ( tiedotNaytolle() )
           printf( "\nTilin saldo %.2lf EUROA.", dSaldo);
        
        break;
        
      case 2:
        dOtto = 40.0;
        if ( dOrigSaldo < dOtto )
           printf("\nTilin saldo ei riita!\n" );
        else{
           dSaldo = dOrigSaldo - dOtto;
           custInfo[nSearchFlag].saldo = dSaldo;
           printf("\nOta kortti.\nNosto onnistui!");
        }
        
         if ( tiedotNaytolle() )
           printf( "\nTilin saldo %.2lf EUROA.", dSaldo);
        break;
        
       case 3:
        dOtto = 60.0;
        if ( dOrigSaldo < dOtto )
           printf("\nTilin saldo ei riita!\n" );
        else{
           dSaldo = dOrigSaldo - dOtto;
           custInfo[nSearchFlag].saldo = dSaldo;
           printf("\nOta kortti.\nNosto onnistui!");
        }
        
         if ( tiedotNaytolle() )
           printf( "\nTilin saldo %.2lf EUROA.", dSaldo);
        break; 
        
       case 4:
        dOtto = 90.0;
        if ( dOrigSaldo < dOtto )
           printf("\nTilin saldo ei riita!\n" );
        else{
           dSaldo = dOrigSaldo - dOtto;
           custInfo[nSearchFlag].saldo = dSaldo;
           printf("\nOta kortti.\nNosto onnistui!");
        }
        
         if ( tiedotNaytolle() )
           printf( "\nTilin saldo %.2lf EUROA.", dSaldo);
        break;
        
       case 5:
        dOtto = 140.0;
        if ( dOrigSaldo < dOtto )
           printf("\nTilin saldo ei riita!\n" );
        else{
           dSaldo = dOrigSaldo - dOtto;
           custInfo[nSearchFlag].saldo = dSaldo;
           printf("\nOta kortti.\nNosto onnistui!");
        }
        
         if ( tiedotNaytolle() )
           printf( "\nTilin saldo %.2lf EUROA.", dSaldo);
        break;
        
       case 6:
        dOtto = 240.0;
        if ( dOrigSaldo < dOtto )
           printf("\nTilin saldo ei riita!\n" );
        else{
           dSaldo = dOrigSaldo - dOtto;
           custInfo[nSearchFlag].saldo = dSaldo;
           printf("\nOta kortti.\nNosto onnistui!");
        }
        
         if ( tiedotNaytolle() )
           printf( "\nTilin saldo %.2lf EUROA.", dSaldo);
        break;
        
       case 7:
        dOtto = 0.0;
        printf("\nAnna summa (kokonaisluku, 10:lla jaettava) > ");
        while ( ( nStatus = scanf("%d%c", &nOtto, &chMki)) == 0 ||
                ( nStatus == 2 && chMki != '\n' ) || !(nOtto %10 == 0) ){
                   if ( nOtto%10 != 0){
                      printf( "\nNostettava summa voi olla vain 10:lla jaettava!");
                      printf("\nAnna summa (kokonaisluku, 10:lla jaettava) > ");
                   }
                   else{
                      while( ( chMerkki = getchar()) != '\n');
                      printf("\nAnnoit roskan %c\n", chMerkki);
                      printf("\nAnna summa (kokonaisluku, 10:lla jaettava) > ");
                   }                  
                }
        dOtto = (double ) nOtto;
        if ( dOrigSaldo < dOtto )
           printf("\nTilin saldo ei riita!\n" );
        else{
           dSaldo = dOrigSaldo - dOtto;
           custInfo[nSearchFlag].saldo = dSaldo;
           printf("\nOta kortti.\nNosto onnistui!");
        }
        
         if ( tiedotNaytolle() )
           printf( "\nTilin saldo %.2lf EUROA.", dSaldo);
        break;
        
        default: 
          printf( "\nJotain meni pieleen. Poistutaan!");
        break;
   }
   
}   

// Tulostetaan asiakkaan saldo 
void tulostaSaldo(CustomerInfo custInfo[], char* strNimi, char* strPin, int nLength){
    int nIndex = 0;
   int nSearchFlag = -1;
   double dOrigSaldo = 0;
      
   // Etsit‰‰n asiakas
   for ( nIndex = 0; nIndex < nLength; nIndex++){
      if  ( strcmp( custInfo[nIndex].name, strNimi) == 0 &&    // Nimi ja
            strcmp( custInfo[nIndex].pin, strPin)   == 0 )     // PIN-koodi t‰sm‰‰v‰t
          nSearchFlag = nIndex;
   }
   
   dOrigSaldo = custInfo[nSearchFlag].saldo;
   printf("\nTilisi saldo: %.2lf euroa.\n", dOrigSaldo);
}

// Tulosta asiakkaan tilitapahtumat
void tulostaTilitapahtumat(CustomerInfo custInfo[], char* strNimi, char* strPin, int nLength){
   printf("\nTilitapahtumat: TAMA TOIMINTO EI OLE KAYTOSSA\n");
}

// Lataa asiakkaan puhelinliittym‰‰n rahaa
void lataaPuheaikaa(CustomerInfo custInfo[], char* strNimi, char* strPin, int nLength){
   printf("\nLadataan liittymaasi rahaa ja annetaan puheaikasi:TAMA TOIMINTO EI OLE KAYTOSSA\n");
}

// Valitse tili (tass‰ ei k‰ytˆss‰)
void valitseTili(CustomerInfo custInfo[], char* strNimi, char* strPin, int nLength){
   printf("\nValitse tilisi -TOIMINTO EI OLE KAYTOSSA\n");
}  

int tiedotNaytolle(void){
   int nVastaus = 0;
   char chAns;
   int nStatus = 0;
   char chMki;
   char chMerkki;
   
   printf("\nHaluatko tiedot naytolle? (k/e) > ");
   while ( ( nStatus = scanf("%c%c", &chAns, &chMki)) == 0 ||
           ( nStatus == 2 && chMki != '\n') || !( chAns == 'k' || chAns == 'e') ){
              if ( !( chAns == 'k' || chAns == 'e' ) ){
                 printf( "\nHaluatko tiedot naytolle? (k/e) > ");
              }
              else{
                 while ( ( chMerkki = getchar() ) != '\n');
                 printf("\nAnnoit roskan %c\n", chMerkki);
                 printf( "\nHaluatko tiedot naytolle? (k/e) > ");
              }
           }
   if ( chAns == 'k')
      nVastaus = 1;
   else
      nVastaus = 0;
      
   return nVastaus;
}


