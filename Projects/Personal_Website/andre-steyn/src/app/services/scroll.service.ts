// scroll.service.ts
import { Injectable } from '@angular/core';
import { Subject, Observable } from 'rxjs';

@Injectable({
  providedIn: 'root',
})
export class ScrollService {
  private scrollSubject = new Subject<string>();

  get scrollObservable(): Observable<string> {
    return this.scrollSubject.asObservable();
  }

  scrollTo(section: string) {
    this.scrollSubject.next(section);
  }
}
