function supprimerAccents(message) {
    return message.normalize("NFD").replace(/[\u0300-\u036f]/g, "");
}

function mettreMaj(message) {
    return message.toUpperCase();
}

function garderLettres(message) {
    return message.replace(/[^a-zA-Z]+/g, '');
}

function addl(char1, char2) {
    return String.fromCharCode((char1.charCodeAt(0) + char2.charCodeAt(0) - 130) % 26 +65 );
}

function sousl(char1, char2) {
    return String.fromCharCode((char1.charCodeAt(0) - char2.charCodeAt(0)+26) % 26 +65 );
}

function codagev(message, mot) {
    message = mettreMaj(supprimerAccents(message));
    mot = mettreMaj(supprimerAccents(mot));

    let l = mot.length;

    let messageCode = "";

    let nb_lettres_cryptes = 0;

    for(let i = 0; i < message.length; i++) {
        if ( message.charCodeAt(i) > 64 && message.charCodeAt(i) < 91) {
            messageCode += addl(message[i], mot[nb_lettres_cryptes % l]);
            nb_lettres_cryptes++;
        }
        else {
            messageCode += message[i];
        }
    }

    return messageCode;
}

function decodagev(message, mot) {
    message = mettreMaj(supprimerAccents(message));
    mot = mettreMaj(supprimerAccents(mot));

    let l = mot.length;

    let messageCode = "";

    let nb_lettres_cryptes = 0;

    for(let i = 0; i < message.length; i++) {
        if ( message.charCodeAt(i) > 64 && message.charCodeAt(i) < 91) {
            messageCode += sousl(message[i], mot[nb_lettres_cryptes % l]);
            nb_lettres_cryptes++;
        }
        else {
            messageCode += message[i];
        }
    }

    return messageCode;
}

function decodage_automatique_v(message, taille_max = 20) {
    message = garderLettres(mettreMaj(supprimerAccents(message)));

    let mots_possibles = new Array();
    for(let i = 0; i < taille_max; i++) {
        mots_possibles.push("");
    }

    let freq_e_min = new Array()
    freq_e_min.push(0);
    for(let i = 1; i < taille_max; i++) {
        freq_e_min.push(100);
    }

    let l = message.length;

    for(let i = 0; i < taille_max; i++) {
        for(let j = 0; j < i; j++) {

            let compte = new Array();
            for(let a = 0; a < 26; a++) {
                compte.push(0);
            }

            for(let a = 0; i * a + j < l; a++) {
                compte[message.charCodeAt(i*a+j)-65]++;
            }

            let max = Math.max(...compte);
            let max_pos = compte.indexOf(max);
            let tot = compte.reduce(function (a, b) {
                return a + b;
              }, 0);

            let freq_max = max / tot * 100;

            if (freq_max < freq_e_min[i]) {
                freq_e_min[i] = freq_max;
            }

            mots_possibles[i] += String.fromCharCode((max_pos - 4 + 26) % 26 + 65);
        }
    }

    return mots_possibles[freq_e_min.indexOf(Math.max(...freq_e_min))];
}

function analyse(message) {
    message = garderLettres(mettreMaj(supprimerAccents(message)));

    let alphabet = new Array();
    for(let i = 0; i < 26; i++) {
        alphabet.push(0);
    }

    for(let i = 0; i < message.length; i++) {
        alphabet[message.charCodeAt(i)-65]++;
    }

    return alphabet;
}

function convertBase(value, from_base, to_base) {
    var range = '0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ+/'.split('');
    var from_range = range.slice(0, from_base);
    var to_range = range.slice(0, to_base);
    
    var dec_value = value.split('').reverse().reduce(function (carry, digit, index) {
      if (from_range.indexOf(digit) === -1) throw new Error('Invalid digit `'+digit+'` for base '+from_base+'.');
      return carry += from_range.indexOf(digit) * (Math.pow(from_base, index));
    }, 0);
    
    var new_value = '';
    while (dec_value > 0) {
      new_value = to_range[dec_value % to_base] + new_value;
      dec_value = (dec_value - (dec_value % to_base)) / to_base;
    }
    return new_value || '0';
  }

  function estPrems(n) {
    // Corner cases
    if (n <= 1)
        return false;
    if (n <= 3)
        return true;
  
    // This is checked so that we can skip
    // middle five numbers in below loop
    if (n % 2 == 0 || n % 3 == 0)
        return false;
  
    for (let i = 5; i * i <= n; i = i + 6)
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
  
    return true;
  }

  function diviseurs(nombre) {
      let nb_diviseurs = new Array();
      for(let i = 0; i < nombre; i++) {
          if(nombre % i == 0) {
              nb_diviseurs.push(i);
          }
      }
      return nb_diviseurs;
  }

  function NbsPremsjusquaN(nombre) {
      let nbprems = new Array();
      nbprems.push(2);

      for(let i = 3; i <= nombre; i++) {
          let estprems = true;
          let nb2 = 0;
          let sqrt_num = Math.sqrt(i);

          while(estprems && (nb2 < nbprems.length) && (nbprems[nb2] <= sqrt_num)) {
              if( i % nbprems[nb2] == 0 ) {
                  estprems = false;
              }
              nb2++;
          } 

          if (estprems) {
              nbprems.push(i);
          }
      }

      return nbprems;
  }

  function farey_approximation(nombre, precision) {
    let nb_int = Math.floor(nombre);
    let nb2 = nombre - nb_int;
    let num_below = 0, den_below = 1, num_above = 1, den_above = 1, num_mediant = 1, den_mediant = 2;

    while (num_mediant < precision && den_mediant < precision)
    {
        if(nb2 > num_mediant/den_mediant)
        {
            num_below = num_mediant;
            den_below = den_mediant;
            num_mediant = num_mediant + num_above;
            den_mediant = den_mediant + den_above;
        }
        else
        {
            num_above = num_mediant;
            den_above = den_mediant;
            num_mediant = num_mediant + num_below;
            den_mediant = den_mediant + den_below;
        }
    }

    return (num_mediant + nb_int*den_mediant).toString() + "/" + (den_mediant).toString();
  }

  function pgcd(a,  b)
{
    if (b == 0)
        return a;
    return pgcd(b,a%b);
}
