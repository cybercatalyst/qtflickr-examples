/******************************************************************************
 *   Copyright (C) 2009 by Evgeni Gordejev   *
 *   evgeni.gordejev@gmail.com   *
 *                                                                            *
 *   This program is free software; you can redistribute it and/or modify     *
 *   it under the terms of the GNU Library Lesser General Public License as   *
 *   published by the Free Software Foundation; either version 2 of the       *
 *   License, or (at your option) any later version.                          *
 *                                                                            *
 *   This program is distributed in the hope that it will be useful,          *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of           *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            *
 *   GNU Lesser General Public License for more details.                      *
 *                                                                            *
 *   You should have received a copy of the GNU Library Lesser General Public *
 *   License along with this program; if not, write to the                    *
 *   Free Software Foundation, Inc.,                                          *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.                *
 ******************************************************************************/

#include "mainwindow.h"
#include "photo.h"
#include <QtGui>

MainWindow::MainWindow()
    : QMainWindow()
{
    // Initialising flickr class with valid apikey and apisecret
    flickr = new Flickr ( "xxx",
                          "xxx",
                          this );

    // connecting listner to the requestFinished() signal
    connect ( flickr,
              SIGNAL ( requestFinished ( int, FlickrResponse, FlickrError, void* ) ),
              this,
              SLOT ( requestFinished ( int, FlickrResponse, FlickrError, void* ) ) );

    photoView = new PhotoView();
    connect ( photoView,SIGNAL ( giveMeMore(int) ),this,SLOT ( getPhotos(int) ) );
    this->setCentralWidget ( photoView );

    getPhotos(MAX_PHOTOS);
}


MainWindow::~MainWindow()
{
}

void MainWindow::getPhotos(int num)
{
    FlickrMethod method;
    method.method = "flickr.photos.getRecent";
    method.args.insert( "per_page", QString().setNum(num) );
    method.args.insert( "extras", "url_s, description" );
    FlickrRequest request;
    request.requests.insert( "photo", "url_s, description" );
    request.requests.insert( "description", "" );
    flickr->get ( method,request );
}

void MainWindow::requestFinished (int reqId, FlickrResponse data, FlickrError err, void* userData )
{
    if ( !err.code )
    {

        QList<FlickrTag> list = data.tags.values("photo");
        QList<FlickrTag> listD = data.tags.values("description");
        for ( int i = 0; i < list.size(); ++i )
        {
            photoView->addPhoto ( list.at ( i ).attrs.value("url_s") );
            qDebug()<<list.at ( i ).attrs.value("url_s");
            qDebug()<<listD.at ( i ).value;
        }

    }
    else
    {
        qDebug() <<err.message;
    }
}
