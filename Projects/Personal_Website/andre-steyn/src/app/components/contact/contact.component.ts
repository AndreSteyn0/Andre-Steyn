import { isPlatformBrowser } from '@angular/common';
import { Component, Inject, OnInit, PLATFORM_ID } from '@angular/core';
import {
  FormControl,
  FormGroup,
  ReactiveFormsModule,
  Validators,
} from '@angular/forms';
import AOS from 'aos';
import 'aos/dist/aos.css';
import { ContactService } from '../../services/contact.service';

@Component({
  selector: 'app-contact',
  standalone: true,
  imports: [ReactiveFormsModule],
  templateUrl: './contact.component.html',
  styleUrl: './contact.component.css',
})
export class ContactComponent implements OnInit {
  public contactForm!: FormGroup;
  public showSuccessMessage = false;

  constructor(
    @Inject(PLATFORM_ID) private platformId: Object,
    private contactService: ContactService
  ) {}

  ngOnInit(): void {
    if (isPlatformBrowser(this.platformId)) {
      AOS.init();
    }

    this.contactForm = new FormGroup({
      name: new FormControl(null, Validators.required),
      email: new FormControl(null, [Validators.required, Validators.email]),
      message: new FormControl(null, Validators.required),
    });
  }

  onSubmit(): void {
    if (this.contactForm.valid) {
      const formValues = this.contactForm.value;

      this.contactService.sendEmail(formValues).subscribe(
        () => {
          console.log('Email sent successfully');
          this.showSuccessMessage = true;
          this.contactForm.reset();
          setTimeout(() => {
            this.showSuccessMessage = false;
          }, 5000);
        },
        (error) => {
          console.error('Error sending email:', error);
          // Handle error as needed
        }
      );
    }
  }
}
