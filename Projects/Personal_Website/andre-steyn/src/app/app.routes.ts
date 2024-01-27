import { Routes } from '@angular/router';

export const routes: Routes = [
  {
    path: '',
    pathMatch: 'full',
    loadComponent: () =>
      import('./components/main/main.component').then(
        (mod) => mod.MainComponent
      ),
  },
  {
    path: 'dariel',
    loadComponent: () =>
      import('./components/experience/detailed/dariel/dariel.component').then(
        (mod) => mod.DarielComponent
      ),
  },
  {
    path: 'minopex-1',
    loadComponent: () =>
      import('./components/experience/detailed/minopex/minopex-first/minopex-first.component').then(
        (mod) => mod.MinopexFirstComponent
      ),
  },
  {
    path: 'minopex-2',
    loadComponent: () =>
      import('./components/experience/detailed/minopex/minopex-second/minopex-second.component').then(
        (mod) => mod.MinopexSecondComponent
      ),
  },
  {
    path: '**',
    redirectTo: ''
  },
];