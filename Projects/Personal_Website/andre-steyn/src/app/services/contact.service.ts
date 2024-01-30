import { HttpClient, HttpHeaders } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { Observable } from 'rxjs';

@Injectable({
  providedIn: 'root',
})
export class ContactService {
  private apiUrl =
    'https://7u2x19jfsk.execute-api.af-south-1.amazonaws.com/default/send-email';

  constructor(private http: HttpClient) {}

  sendEmail(body: any): Observable<any> {
    const headers = new HttpHeaders({
      'Content-Type': 'application/json',
    });

    return this.http.post(this.apiUrl, body, { headers });
  }
}
