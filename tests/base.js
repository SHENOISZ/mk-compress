/**
 * Created by shenoisz on 23/06/16.
 */

/// Globals

var documento = $( document );

var mozilla = navigator.userAgent.split('Firefox')[1];
var pagina = $('html, body');

if ( mozilla == undefined ) {

    var pagina = $('body') || $('html, body');
}

///

/*   funçao de busca com ajax   */

var input = $('.base-input-custom'),
    result = $('.base-result');

function consulta( ) {

    var valor = input.val( );

    if (valor.length > 3) {

        $.ajax({
            type: 'GET',
            url: '/busca?q=' + valor,
            success: function ( data ) {

                var input = '<button type="submit" class="btn btn-info base-btn-busca" style="color:#ffffff;">Mais resultados</buttom>';
                try {
                    var html = data.toString( ).split('<section id="busca" class="span8">')[1].split('</section>')[0];
                    html = html.split('<table class="table table-striped">')[1].split('</table>')[0];
                    html = '<table class="table">' + html + '</table>'+ input;
                } catch ( exception ) {
                    var html = '';
                }

                result.html('');
                result.html( html );
                result.css('display', 'block');
            }
        });
    }
}


/*    funçoes da busca    */

var btn_close = $('.btn-close'),
    lupa = $('.icon-lupa'),
    lupa_gray = $('.icon-lupa-gray');

input.focusin( function ( ) {

        btn_close.css('color', '#007FFF');
        lupa.css('display', 'none');
        lupa_gray.css('display', 'block');
        input.css('color', '#007FFF');

} ).focusout( function ( ) {

        lupa.css('display', 'block');
        lupa_gray.css('display', 'none');
        input.css('color', '#ffffff');
        btn_close.css('color', '#ffffff');
        //result.css('display', 'none');

        if (input.val( ) == '') {

            btn_close.css('display', 'none');
            result.css('display', 'none');
        }
} );

/*    verifica se esta sendo digitado algo    */

input.keydown( function ( ) {

    if (input.val( ) != '') {

        btn_close.css('display', 'block');
        btn_close.css('color', '#007FFF');
        consulta( );
    } else {

        btn_close.css('display', 'none');
        result.css('display', 'none');
    }

} );

/*    limpa a busca   */

btn_close.click( function ( ) {

    input.val('');
    btn_close.css('display', 'none');
    result.css('display', 'none');
} );


/*  exibir aba novidades */

var novidades_aba = $('.novidades-aba'),
    conteudo_novidades = $('.conteudo-novidades-aba');

$('.menu-novidades-item, .novidades-aba').mouseover( function ( ) {

    novidades_aba.animate( );
    novidades_aba.animate({'height': '305px'}, 300);
    conteudo_novidades.animate( );
    conteudo_novidades.animate({'height': '300px'}, 300);
} );

$('.menu-custom, .novidades-aba').mouseout( function ( ) {

    novidades_aba.animate( );
    novidades_aba.animate({'height': '0'}, 300);
    conteudo_novidades.animate({'height': '0'}, 300);
    conteudo_novidades.animate( );
} );

/*  exibir aba jogos online */

var novidades_aba_games = $('.jogos-online-aba');

$('.menu-jogos-online-item, .jogos-online-aba').mouseover( function ( ) {

    novidades_aba_games.animate( );
    novidades_aba_games.animate({'height': '305px'}, 300);
    conteudo_novidades.animate( );
    conteudo_novidades.animate({'height': '300px'}, 300);
} );

$('.menu-custom, .jogos-online-aba').mouseout( function ( ) {

    novidades_aba_games.animate( );
    novidades_aba_games.animate({'height': '0'}, 300);
    conteudo_novidades.animate({'height': '0'}, 300);
    conteudo_novidades.animate( );
} );


var scrollup = true,
    scrolldown = true,
    back_top = $('.back-top');

documento.scroll( function ( ) {

    /* nav-bar-ocultar */

    var navbar = $('.base-navbar');

    if ( pagina.width( ) > 800 ) {

        if ( pagina.scrollTop( ) > 50 ) {

            if ( scrollup ) {

                navbar.animate();
                navbar.animate({'top': '-75px'}, 300);
                navbar.animate({'opacity': '0.90'}, 300);
                scrollup = false;
                scrolldown = true;
            }
        } else {

            if ( scrolldown ) {

                navbar.animate();
                navbar.animate({'top': '0'}, 300);
                navbar.animate({'opacity': '100.0'}, 300);
                scrollup = true;
                scrolldown = false;
            }
        }
    } else {

        navbar.animate( );
        navbar.animate({'top': '0'}, 300);
        navbar.animate({'opacity': '100.0'}, 300);
    }

    if ( pagina.scrollTop( ) < 800 ) {

        back_top.css('display', 'none');
    } else {

        back_top.css('display', 'block');
    }

} );


/* funcao busca mobile */

var base_buscaform_mobile = $('.base-buscaform-mobile');

$('.btn-view-custom-mobile').click( function ( ) {

    base_buscaform_mobile.animate( {'left': '30px'}, 500, function ( ) {

        $('.input-base-custom-mobile').focus( );
    } );
} );

$('.btn-base-custom-mobile').click( function ( ) {

    base_buscaform_mobile.submit( );
} );

$('.input-base-custom-mobile').focusout( function ( ) {

    var input = this;
    base_buscaform_mobile.animate( {'left': '-290px'}, 500, function ( ) {

        input.value = '';
    } );
} );


// change number for stars

function get_score( ) {

   $('.get-scores .get-score').each( function ( ) {

       var score = $(this);
       var value = score.html().trim();

       switch (value) {

           case '0.0':
               score.html(' ');
               break;

           case '0.5':
               score.html('✰');
               break;

           case '1.0':
               score.html('★');
               break;

           case '1.5':
               score.html('★ ✰');
               break;

           case '2.0':
               score.html('★ ★');
               break;

           case '2.5':
               score.html('★ ★ ✰');
               break;

           case '3.0':
               score.html('★ ★ ★');
               break;

           case '3.5':
               score.html('★ ★ ★ ✰');
               break;

           case '4.0':
               score.html('★ ★ ★ ★');
               break;

           case '4.5':
               score.html('★ ★ ★ ★ ✰');
               break;

           case '5.0':
               score.html('★ ★ ★ ★ ★');
               break;

           default:
               score.html(' ');
               break;
       }

   });
}

/* footer funcoes  */

back_top.click( function ( ) {

    if ( pagina.scrollTop( ) > 400 ) {

        pagina.animate({'scrollTop': 0}, 800);
    }
} );

/* function for get image error if for case, only img */
function fn_onerror( args ) {

    $( args ).attr('src', '/static/img/novas/no-image.svg');
}

/* function for get image error if for case, only figure  */
function fn_error( ) {

    $('body .conteudo-container-box figure, ' +
        '.conteudo-container-box-mini figure,' +
        '.container-custom figure,' +
        '.swiper-container .imagem-slide').each( function ( ) {

        var obj = $( this );
        var imagem = obj.attr('data-src');

        if ( imagem == '' ) {

            obj.css({'background-image': 'url("/static/img/novas/no-image.svg")'})
                .css({'-webkit-background-image': 'url("/static/img/novas/no-image.svg")'});
        }

    } );
}

// size of page or container
function tam( image ) {
    return image.width( )+ 'x'+ image.height( );
}

// plugin thumbnail
$('body .thumbnails-crop').each( function ( ) {

    var image = $( this );
    var url = image.attr('thumbnail');
    var vazio = image.attr('data-src');

    if ( vazio != '' ) {
        var options = image.attr('thumbnail-options');
        options = options.toString().split(',');

        var config = {};

        for (var i = 0; i < options.length; i++) {
            config[options[i].split(':')[0]] = options[i].split(':')[1];
        }

        config.size = (config.size == 'auto') ? tam(image) : config.size;

        if (config.quality == 'undefined') {
            config.quality = 96;
        }

        if (config.crop == 'undefined') {
            config.crop = 'center';
        }

        $.ajax({
            url: '/thumbnail?thumbs=' + url + '&size=' + config.size + '&quality=' + config.quality + '&crop=' + config.crop,
            type: 'get',
            success: function (data) {

                image.css({'background-image': 'url("' + data + '")'}).
                    css({'-webkit-background-image': 'url("' + data + '")'});
                //console.log( data );
            }
        });
    }
});

/*   finalizar o loading    */

documento.ready( function ( ) {

    $('.load-page-all').css('display', 'none');
    fn_error( );
    get_score( );
} );
